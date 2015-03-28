/*
  ATtiny85SerialHello.ino: Repeatedly print "hello" and blink an LED.
  Copyright Jason Pepas (Pepas Labs, LLC)
  Released under the terms of the MIT License.  See http://opensource.org/licenses/MIT
*/

#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include <SoftwareSerial.h>
#include <WOTinySoftSPI.h>
#include <MCP4801SoftSPI.h>

#include "command_t.h"

// ATiny85 pinout:
//
//                                      +--\/--+
//        (PCINT5/!RESET/ADC0/dW) PB5  -|1    8|-  VCC
// (PCINT3/XTAL1/CLKI/!OC1B/ADC3) PB3  -|2    7|-  PB2 (SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
//  (PCINT4/XTAL2/CLKO/OC1B/ADC2) PB4  -|3    6|-  PB1 (MISO/DO/AIN1/OC0B/OC1A/PCINT1)
//                                GND  -|4    5|-  PB0 (MOSI/DI/SDA/AIN0/OC0A/!OC1A/AREF/PCINT0)
//                                      +------+

#define ARDUINO_PIN_D0 0
#define ARDUINO_PIN_D1 1
#define ARDUINO_PIN_D2 2
#define ARDUINO_PIN_D3 3
#define ARDUINO_PIN_D4 4
#define ARDUINO_PIN_D5 5

#define ATTINY_PIN_1 ARDUINO_PIN_D5
#define ATTINY_PIN_2 ARDUINO_PIN_D3
#define ATTINY_PIN_3 ARDUINO_PIN_D4
#define ATTINY_PIN_5 ARDUINO_PIN_D0
#define ATTINY_PIN_6 ARDUINO_PIN_D1
#define ATTINY_PIN_7 ARDUINO_PIN_D2

// project pinout:
//
//                      +--\/--+
//                 D5  -|1    8|-  Vcc
//  TTL serial RX  D3  -|2    7|-  D2  SPI chip select (to DAC)
//  TTL serial TX  D4  -|3    6|-  D1  SPI SCK (to DAC)
//                GND  -|4    5|-  D0  SPI MOSI (to DAC)
//                      +------+

#define SoftSPI_MOSI_pin ARDUINO_PIN_D0
#define SoftSPI_SCK_pin ARDUINO_PIN_D1
#define MCP4801_SLAVESELECTLOW_pin ARDUINO_PIN_D2
#define MCP4801_LDACLOW_pin PIN_NOT_CONNECTED
#define MCP4801_SHUTDOWNLOW_pin PIN_NOT_CONNECTED

#define RX_pin ARDUINO_PIN_D3
#define TX_pin ARDUINO_PIN_D4

// --- SPI / MCP4801 DAC setup

WOTinySoftSPI mySPI(SoftSPI_MOSI_pin, SoftSPI_SCK_pin);

MCP4801SoftSPI voltageDAC(MCP4801_SLAVESELECTLOW_pin,
                          MCP4801_LDACLOW_pin,
                          MCP4801_SHUTDOWNLOW_pin,
                          &mySPI
                         );

// --- serial port setup

SoftwareSerial serial(RX_pin, TX_pin);

/*

Serial terminal interface:

Set the output voltage to 5 volts:

    v5.000;

Set the bits in the DAC to 0xFF (8-bit DAC):

    xFF;

Set the bits in the DAC to 0x3FF (10-bit DAC):

    x3FF;

Set the bits in the DAC to 0xFFF (12-bit DAC):

    xFFF;

Increase the DAC output by one LSB:

    +;

Decrease the DAC output by one LSB:

    -;

*/

#define MIN_EXPECTED_LEN 2 // +;
#define MAX_EXPECTED_LEN 8 // v12.345;

uint16_t DAC_bits = 0;

#define MCP4801_NUM_BITS 8
#define MCP4811_NUM_BITS 10
#define MCP4821_NUM_BITS 12

uint8_t DAC_num_bits = MCP4801_NUM_BITS;

#define BUFF_LEN (MAX_EXPECTED_LEN + sizeof('\0'))
char buffer[BUFF_LEN];
char *buff_ptr;

void setup()
{
  serial.begin(9600);
  
  // start up the SPI bus
  mySPI.begin();
  mySPI.setBitOrder(MSBFIRST);
  mySPI.setDataMode(SPI_MODE0);

  // start controlling the voltage supply
  voltageDAC.begin();  

  memset(buffer, 0, sizeof(buffer));
  buff_ptr = buffer;
}

void loop()
{
  command_t command = read_command(&serial, buffer, BUFF_LEN);

  bool ok;
    
  if (command = COMMAND_INCREMENT)
  {
    ok = increment_output_voltage();
  }
  else if (command = COMMAND_DECREMENT)
  {
    ok = decrement_output_voltage();
  }
  else if (command = COMMAND_SET_VOLTS)
  {
    ok = parse_and_run_voltage_command(buffer);
  }
  else if (command = COMMAND_SET_HEX)
  {
    ok = parse_and_run_hex_command(buffer);
  }
  else
  {
    ok = false;
  }

  if (ok)
  {
    ack();
  }
  else
  {
    nope('a');
  }
}

command_t read_command(SoftwareSerial *serial, char *buffer, uint8_t buff_len)
{
  if (buff_len < 2)
  {
    return COMMAND_UNKNOWN;
  }

  // --- read the first character
  
  while(serial->available() == 0)
  {
    continue;
  }
    
  char ch = serial->read();
  
  if (ch == '+')
  {
    uint8_t num_chars_consumed = consume_until_sentinel(serial, ';');
    if (num_chars_consumed == 1)
    {
      return COMMAND_INCREMENT;
    }
    else
    {
      return COMMAND_UNKNOWN;
    }
  }
  else if (ch == '-')
  {
    uint8_t num_chars_consumed = consume_until_sentinel(serial, ';');
    if (num_chars_consumed == 1)
    {
      return COMMAND_DECREMENT;
    }
    else
    {
      return COMMAND_UNKNOWN;
    }
  }
  else if (ch == 'x')
  {
    // prepend buffer with '0x'
    buffer[0] = '0';
    buffer[1] = 'x';
    buff_ptr = buffer+2;
    
    // read the hex characters into buffer
    bool reached_sentinel = read_until_sentinel(serial, buffer, buff_len-2, ';');    
    if (!reached_sentinel)
    {
      return COMMAND_UNKNOWN;
    }
    else
    {
      return COMMAND_SET_HEX;
    }
  }
  else if (ch == 'v')
  {
    // read the floating point string into buffer
    bool reached_sentinel = read_until_sentinel(serial, buffer, buff_len, ';');
    if (!reached_sentinel)
    {
      return COMMAND_UNKNOWN;
    }
    else
    {
      return COMMAND_SET_VOLTS;
    }
  }
  else
  {
    return COMMAND_UNKNOWN;
  }
}

uint8_t consume_until_sentinel(SoftwareSerial *serial, char sentinel)
{
  uint8_t num_chars_consumed = 0;
  
  while(true)
  {
    while(serial->available() == 0)
    {
      continue;
    }
    
    char ch = serial->read();
    num_chars_consumed++;
    
    if (ch == sentinel || num_chars_consumed == UINT8_MAX)
    {
      return num_chars_consumed;
    }
  }
}

bool read_until_sentinel(SoftwareSerial *serial, char *buffer, uint8_t buff_len, char sentinel)
{
  uint8_t num_chars_consumed = 0;
  char *buff_ptr = buffer;
  
  while(true)
  {
    while(serial->available() == 0)
    {
      continue;
    }
    
    *buff_ptr = serial->read();
    num_chars_consumed++;

    if (*buff_ptr == sentinel)
    {
      *buff_ptr = '\0';
      bool sentinel_reached = true;
      return sentinel_reached;
    }
    else if (num_chars_consumed == buff_len-1)
    {
      *buff_ptr = '\0';
      bool sentinel_reached = false;
      return sentinel_reached;
    }
    else
    {
      buff_ptr++;
      continue;
    }  
  }
}

void nope(char ch)
{
  serial.print("!");
  serial.print(ch);
  serial.print(";");
  serial.flush();
}  

void ack()
{
  serial.print(".");
  serial.flush();
}

void set_DAC_bits(uint8_t bits)
{
  bool use_2x_gain = true;
  voltageDAC.setVoltageOutputBits(DAC_bits, use_2x_gain);
}

bool DAC_would_overflow(uint8_t num_bits)
{
  return DAC_bits == (1 << num_bits);
}

bool DAC_would_underflow()
{
  return DAC_bits == 0;
}

bool increment_output_voltage()
{
  if (DAC_would_overflow(DAC_num_bits))
  {
    return false;
  }

  DAC_bits++;
  set_DAC_bits(DAC_bits);
  return true;
}

bool decrement_output_voltage()
{
  if (DAC_would_underflow())
  {
    return false;
  }

  DAC_bits--;
  set_DAC_bits(DAC_bits);
  return true;
}

bool parse_and_run_voltage_command(char *buffer)
{
  float v = 0;
  int num_matches_found = sscanf(buffer, "%f", &v);
  if (num_matches_found != 1)
  {
    return false;
  }
  
  voltageDAC.setVoltageOutput(v);
  return true;
}

bool parse_and_run_hex_command(char *buffer)
{
  uint16_t bits = 0;
  int num_matches_found = sscanf(buffer, "%x", &bits);
  if (num_matches_found != 1)
  {
    return false;
  }

  DAC_bits = bits;
  set_DAC_bits(DAC_bits);
  return true;
}

