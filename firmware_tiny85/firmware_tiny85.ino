/*
  firmware_tiny85.ino: Arduino sketch for the Programmable LM317 project.  See https://github.com/pepaslabs/ProgrammableLM317
  Copyright Jason Pepas (Pepas Labs, LLC)
  Released under the terms of the MIT License.  See http://opensource.org/licenses/MIT
*/

#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include "features.h"

#include <SoftwareSerial.h>

#include "buffer.h"
#include "pins.h"
#include "SPI_util.h"
#include "DAC_util.h"
#include "MCP4821.h"

#include "command.h"


// ATtiny85 pinout:
//
//                            +--\/--+
//                       D5  -|1    8|-  Vcc   (to 5V)
//      TTL serial RX    D3  -|2    7|-  D2    SPI CS (to DAC CS, pin 2)
//      TTL serial TX    D4  -|3    6|-  D1    SPI SCK (to DAC SCK, pin 3)
//                      GND  -|4    5|-  D0    SPI MOSI (to DAC SDI, pin 4)
//                            +------+

// MCP4821 pinout:
//
//                            +--\/--+
//             (to 5V)  Vcc  -|1    8|-  Vout
//   (to tiny85 pin 5)  ~CS  -|2    7|-  GND
//   (to tiny85 pin 7)  SCK  -|3    6|-  ~SHDN  (to 5V)
//   (to tiny85 pin 6)  SDI  -|4    5|-  ~LDAC  (to GND)
//                            +------+


// --- DAC / SPI setup:


DAC_config_t dac_config = MCP4821_config();

DAC_data_t dac_data = { .config = &dac_config, .gain = false, .code = 0x0 };


SPI_bus_t spi_bus = { .MOSI_pin = ATTINY85_PIN_5,
                      .MISO_pin = PIN_NOT_CONNECTED,
                      .SCK_pin = ATTINY85_PIN_6
                    };
                    
SPI_device_t spi_dac = { .bus = &spi_bus,
                         .CS_pin = ATTINY85_PIN_7,
                         .bit_order = MSBFIRST
                       };


// --- Serial setup:


#define RX_pin ATTINY85_PIN_2
#define TX_pin ATTINY85_PIN_3

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

Set the DAC output code to 255, no gain:

    c255;

Set the DAC output code to 4095 (12-bit DAC), with 2x gain:

    C4095;

Increase the DAC output by one LSB:

    +;

Decrease the DAC output by one LSB:

    -;

FIXME: should I also support 'XFF;', which is the equivalent of 'xFF;' but with gain bit set?
*/

#define MIN_EXPECTED_BUFF_LEN 2 // "+;"
#define MAX_EXPECTED_BUFF_LEN 9 // "v12.3456;"
#define BUFF_LEN (MAX_EXPECTED_BUFF_LEN + sizeof('\0'))

char buffer_bytes[BUFF_LEN];
char_buffer_t buffer = { .len = BUFF_LEN, .bytes = buffer_bytes };

char *buff_ptr;


void setup()
{
  serial.begin(9600);

  #ifdef HAS_BOOT_MESSAGE
  {
    delay(1);
    serial.print("OK;");
    serial.flush();
  }
  #endif
  
  // setup soft SPI
  pinMode(spi_bus.MOSI_pin, OUTPUT);
  pinMode(spi_bus.SCK_pin, OUTPUT);
  pinMode(spi_dac.CS_pin, OUTPUT);
  
  digitalWrite(spi_dac.CS_pin, HIGH); // start with the DAC un-selected.

  clear_char_buffer(&buffer);
  buff_ptr = (buffer.bytes); // FIXME can I delete this?
}


void loop()
{
  command_t command = read_command(&serial, buffer.bytes, buffer.len);
  if (command >= END_OF_COMMANDS_SECTION)
  {
    #ifdef HAS_ERROR_PRINTING
    {
      printError(command);
    }
    #endif
    return;
  }

  error_t error;
  
  switch(command)
  {
    
    #ifdef HAS_INCREMENT_COMMAND
    case COMMAND_INCREMENT:
    {
      error = increment_output_voltage(&dac_data, &spi_dac);
      break;
    }
    #endif
  
    #ifdef HAS_DECREMENT_COMMAND
    case COMMAND_DECREMENT:
    {
      error = decrement_output_voltage(&dac_data, &spi_dac);
      break;
    }
    #endif
  
    #ifdef HAS_VOLTS_COMMAND
    case COMMAND_SET_VOLTS:
    {
      error = parse_and_run_voltage_command(buffer.bytes, &dac_data, &spi_dac);
      break;
    }
    #endif
  
    #ifdef HAS_HEX_COMMAND
    case COMMAND_SET_HEX:
    {
      error = parse_and_run_hex_command(buffer.bytes, &dac_data, &spi_dac);
      break;
    }
    #endif
  
    #ifdef HAS_CODE_COMMAND
    case COMMAND_SET_CODE:
    {
      error = parse_and_run_code_command(buffer.bytes, &dac_data, &spi_dac);
      break;
    }
    #endif
  
    default:
    {
      error = ERROR_UNKNOWN_COMMAND;
      break;
    }
  }
  
  if (error != OK_NO_ERROR)
  {
    #ifdef HAS_ERROR_PRINTING
    {
      printError(error);
    }
    #endif
    return;
  }
  
  #ifdef HAS_SUCCESS_PRINTING
  {
    printSuccess(command);
  }
  #endif
}


command_t read_command(SoftwareSerial *serial, char *buffer, uint8_t buff_len)
{
  // --- read the first character
  
  while(serial->available() == 0)
  {
    continue;
  }
    
  char ch = serial->read();
  
  switch(ch)
  {
    #ifdef HAS_INCREMENT_COMMAND
    case '+':
    {
      uint8_t num_chars_consumed = consume_until_sentinel(serial, ';');
      if (num_chars_consumed == 1)
      {
        return COMMAND_INCREMENT;
      }
      else
      {
        return ERROR_PARSING_INCREMENT_COMMAND;
      }
    }
    #endif
    
    #ifdef HAS_DECREMENT_COMMAND
    case '-':
    {
      uint8_t num_chars_consumed = consume_until_sentinel(serial, ';');
      if (num_chars_consumed == 1)
      {
        return COMMAND_DECREMENT;
      }
      else
      {
        return ERROR_PARSING_DECREMENT_COMMAND;
      }
    }
    #endif
    
    #ifdef HAS_HEX_COMMAND
    case 'x':
    {
      // prepend buffer with '0x'
      buffer[0] = '0';
      buffer[1] = 'x';
      buff_ptr = buffer+2;
    
      // read the hex characters into the buffer
      error_t error = read_until_sentinel(serial, buffer, buff_len-2, ';');    
      if (error == OK_NO_ERROR)
      {
        return COMMAND_SET_HEX;
      }
      else // i.e. if (error == ERROR_BUFFER_FILLED_UP_BEFORE_SENTINEL_REACHED)
      {      
        return ERROR_BUFFER_FILLED_UP_BEFORE_SENTINEL_REACHED_WHILE_PARSING_HEX_COMMAND;
      }
    }
    #endif

    #ifdef HAS_VOLTS_COMMAND
    case 'v':
    {
      // read the floating point string into the buffer
      error_t error = read_until_sentinel(serial, buffer, buff_len, ';');
      if (error == OK_NO_ERROR)
      {
        return COMMAND_SET_VOLTS;
      }
      else // i.e. if (error == ERROR_BUFFER_FILLED_UP_BEFORE_SENTINEL_REACHED)
      {      
        return ERROR_BUFFER_FILLED_UP_BEFORE_SENTINEL_REACHED_WHILE_PARSING_VOLTS_COMMAND;
      }
    }
    #endif
    
    
    #ifdef HAS_VOLTS_COMMAND
    case 'c':
    {
      // read the code string into the buffer
      error_t error = read_until_sentinel(serial, buffer, buff_len, ';');
      if (error == OK_NO_ERROR)
      {
        return COMMAND_SET_CODE;
      }
      else // i.e. if (error == ERROR_BUFFER_FILLED_UP_BEFORE_SENTINEL_REACHED)
      {      
        return ERROR_BUFFER_FILLED_UP_BEFORE_SENTINEL_REACHED_WHILE_PARSING_CODE_COMMAND;
      }
    }
    #endif
    
    
    default:
    {
      return ERROR_UNKNOWN_COMMAND;
    }
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


error_t read_until_sentinel(SoftwareSerial *serial, char *buffer, uint8_t buff_len, char sentinel)
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
      return OK_NO_ERROR;
    }
    else if (num_chars_consumed == buff_len-1)
    {
      *buff_ptr = '\0';
      return ERROR_BUFFER_FILLED_UP_BEFORE_SENTINEL_REACHED;
    }
    else
    {
      buff_ptr++;
      continue;
    }  
  }
}


void send_dac_data(DAC_data_t *dac_data, SPI_device_t *spi_dac)
{
  MCP4821_packet_t packet = dac_data_as_MCP4821_packet(dac_data);
  spi_write_MCP4821_packet(spi_dac, packet);
}


#ifdef HAS_INCREMENT_COMMAND
error_t increment_output_voltage(DAC_data_t *dac_data, SPI_device_t *spi_dac)
{
  if (dac_data_increment_code(dac_data) == false)
  {
    return ERROR_INCREMENT_WOULD_CAUSE_OVERFLOW;
  }

  send_dac_data(dac_data, spi_dac);
  return OK_NO_ERROR;
}
#endif


#ifdef HAS_DECREMENT_COMMAND
error_t decrement_output_voltage(DAC_data_t *dac_data, SPI_device_t *spi_dac)
{
  if (dac_data_decrement_code(dac_data) == false)
  {
    return ERROR_DECREMENT_WOULD_CAUSE_UNDERFLOW;
  }

  send_dac_data(dac_data, spi_dac);
  return OK_NO_ERROR;
}
#endif

#define LM317_VREF 1.25
#define GAIN 4.3

#ifdef HAS_VOLTS_COMMAND
error_t parse_and_run_voltage_command(char *buffer, DAC_data_t *dac_data, SPI_device_t *spi_dac)
{
  float output_volts = atof(buffer);
  
  #ifdef HAS_VOLTS_COMMAND_DEBUGGING
  {
    serial.println();
    serial.print("parsed volts: ");
    serial.println(output_volts, 4);
    serial.flush();
  }
  #endif

  if (output_volts < 0)
  {
    return ERROR_PARSED_VOLTAGE_OUTSIDE_SUPPORTED_RANGE;
  }
  
  float DAC_volts = (output_volts - LM317_VREF) / GAIN;
    
  if (dac_data_set_voltage(dac_data, DAC_volts) == false)
  {
    return ERROR_PARSED_VOLTAGE_OUTSIDE_SUPPORTED_RANGE;
  }
  
  MCP4821_packet_t packet = dac_data_as_MCP4821_packet(dac_data);
  spi_write_MCP4821_packet(spi_dac, packet);
  
  return OK_NO_ERROR;
}
#endif


#ifdef HAS_HEX_COMMAND
error_t parse_and_run_hex_command(char *buffer, DAC_data_t *dac_data, SPI_device_t *spi_dac)
{
  uint16_t new_code = 0;
  
  int num_matches_found = sscanf(buffer, "%x", &new_code);
  if (num_matches_found != 1)
  {
    return ERROR_PARSING_HEX_VALUE;
  }

  if (dac_data_set_code(dac_data, new_code) == false)
  {
    return ERROR_PARSED_HEX_OUTSIDE_SUPPORTED_RANGE;
  }
  
  send_dac_data(dac_data, spi_dac);
  return OK_NO_ERROR;
}
#endif


#ifdef HAS_CODE_COMMAND
error_t parse_and_run_code_command(char *buffer, DAC_data_t *dac_data, SPI_device_t *spi_dac)
{
  uint16_t new_code = 0;
  
  int num_matches_found = sscanf(buffer, "%u", &new_code);
  if (num_matches_found != 1)
  {
    return ERROR_PARSING_CODE_VALUE;
  }

  if (dac_data_set_code(dac_data, new_code) == false)
  {
    return ERROR_PARSED_CODE_OUTSIDE_SUPPORTED_RANGE;
  }
  
  send_dac_data(dac_data, spi_dac);
  return OK_NO_ERROR;
}
#endif


#ifdef HAS_ERROR_PRINTING
void printError(error_t error)
{
  serial.print("!e");
  serial.print(error);
  serial.print(";");
  serial.flush();
}
#endif


#ifdef HAS_SUCCESS_PRINTING
void printSuccess(command_t command)
{
  serial.print("ok");
  serial.print(command);
  serial.print(";");
  serial.flush();
}
#endif

