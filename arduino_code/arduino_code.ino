/*
  ATtiny85SerialHello.ino: Repeatedly print "hello" and blink an LED.
  Copyright Jason Pepas (Pepas Labs, LLC)
  Released under the terms of the MIT License.  See http://opensource.org/licenses/MIT
*/

#include <SoftwareSerial.h>
#include <WOTinySoftSPI.h>
#include <MCP4801SoftSPI.h>

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

SoftwareSerial mySerial(RX_pin, TX_pin);

void setup()
{
  mySerial.begin(9600); // SERIAL_7E1
  // hrmmm... SoftwareSerial doesn't support parity.  bummer.
  // however, if we are only dealing with 7-bit ASCII, we can
  // just implement our own parity (and the other host can
  // configure their connection as 7E1).
  
  // start up the SPI bus
  mySPI.begin();
  mySPI.setBitOrder(MSBFIRST);
  mySPI.setDataMode(SPI_MODE0);

  // start controlling the voltage supply
  voltageDAC.begin();  
}

/*

Serial terminal interface:

To set the output voltage to 5 volts:

    v5.000;

To set the bits in the DAC to 0xFF (8-bit DAC):

    0xFF;

To set the bits in the DAC to 0x3FF (10-bit DAC):

    0x3FF;

To set the bits in the DAC to 0xFFF (12-bit DAC):

    0xFFF;

To increase the DAC output by one LSB:

    +;

To decrease the DAC output by one LSB:

    -;

*/

#define MIN_EXPECTED_LEN 2 // +;
#define MAX_EXPECTED_LEN 8 // v12.345;

/*
the ';' character sent using SERIAL_8N1 looks like this in binary:

  0b00111011
  
sent using SERIAL_7E1, it looks like this:

  0b01110111

which is the same as a 'w' sent over SERIAL_8N1:

  0b01110111

so we can use the stock SoftwareSerial.readBytesUntil(), but listen for 'w'.
*/

#define SEMICOLON_WITH_EVEN_PARITY 'w'

uint16_t DAC_bits = 0;

#define MCP4801_NUM_BITS 8
#define MCP4811_NUM_BITS 10
#define MCP4821_NUM_BITS 12

uint8_t DAC_num_bits = MCP4801_NUM_BITS;

#define COMMAND_SENTINEL ';'

#define BUFF_LEN (MAX_EXPECTED_LEN + sizeof('\0'))
char buffer[BUFF_LEN];


void loop()
{
  memset(buffer, 0, sizeof(buffer));
  bool ok;
  
  uint8_t num_bytes_read = mySerial.readBytesUntil('z', buffer, MAX_EXPECTED_LEN);
  if (num_bytes_read < MIN_EXPECTED_LEN)
  {
    nope('a');
    return;
  }
  
  if (buffer[num_bytes_read - 1] != COMMAND_SENTINEL)
  {
    nope('b');
    return;
  }

  buffer[num_bytes_read] = '\0';
  
  /*
  bool ok = check_and_strip_parity_from_buffer(buffer, (num_bytes_read - 1));
  if (!ok)
  {
    nope();
    return;
  }
  */

  if (buffer[0] == '+')
  {
    ok = increment_output_voltage();
  }
  else if (buffer[0] == '-')
  {
    ok = decrement_output_voltage();
  }
  else if (buffer[0] == 'v')
  {
    ok = parse_and_run_voltage_command(buffer);
  }
  else if (buffer[0] == '0')
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
    nope('c');
  }
}

void nope(char ch)
{
  mySerial.print(ch);
  mySerial.flush();
}  

void ack()
{
  mySerial.print(".");
  mySerial.flush();
}

/*
bool check_and_strip_parity_from_buffer(char *buffer, uint8_t len)
{
  for (uint8_t i=0; i < len; i++)
  {
    bool ok = check_and_strip_parity_from_byte(&buffer[i]);
    if (!ok)
    {
      return false;
    }
  }
}

bool check_and_strip_parity_from_byte(char *buffer)
{
  uint8_t byte_with_parity = buffer[0];
  uint8_t decoded_byte = byte_with_parity >> 1;
  uint8_t received_parity_bit = byte_with_parity % 1;
  uint8_t expected_parity_bit = decoded_byte % 1;
  buffer[0] = decoded_byte;
  return (expected_parity_bit == received_parity_bit);
}
*/

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
  int num_matches_found = sscanf(buffer, "%f", &v+1);
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
