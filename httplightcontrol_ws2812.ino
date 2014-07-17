#include <XBee.h>
#include <SPI.h>


#include "wireless_neopixel.h"
#include <Adafruit_NeoPixel.h>

XBee xbee = XBee();

const uint8_t NUM_LEDS = 32;
const uint8_t DATA_PIN = 10;
const uint8_t CLOCK_PIN = 11;

Adafruit_NeoPixel strip( NUM_LEDS, DATA_PIN );
WirelessNeoPixel relay( &strip );

void on_control_command(WirelessClient * lc, uint8_t * data, uint8_t data_length)
{
    uint8_t color = data[0];
    relay.transition_color( color, COLOR_TRANSITION_TIME );
}


void setup()
{ 
  Serial.begin(9600);
#if USE_SOFTWARE_SERIAL > 0
  ss.begin(9600);
  xbee.setSerial( ss );
#else
  xbee.setSerial( Serial );
#endif
  
  // setup light client commands
  relay.map_command( CMD_CONTROL_LIGHT, on_control_command );
  
  // initially off
  relay.set_color( 0 );
}

void loop()
{
    relay.read_packet( xbee );
    relay.show();
}

