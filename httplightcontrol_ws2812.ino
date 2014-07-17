#include <XBee.h>

// Designed for use with an Arduino Pro Mini 5v

#include "wirelessclient.h"
#include <Adafruit_NeoPixel.h>

XBee xbee = XBee();

const uint8_t NUM_LEDS = 30;
const uint8_t DATA_PIN1 = 10;
const uint8_t DATA_PIN2 = 7;

Adafruit_NeoPixel strip1( NUM_LEDS, DATA_PIN1 );
Adafruit_NeoPixel strip2( NUM_LEDS, DATA_PIN2 );
WirelessClient relay;

void set_color( Adafruit_NeoPixel& strip, uint8_t r, uint8_t g, uint8_t b )
{
  for( int i = 0; i < strip.numPixels(); ++i )
  {
    strip.setPixelColor( i, strip.Color(r, g, b) );
  }
} // set_color

void on_control_command(WirelessClient * lc, uint8_t * data, uint8_t data_length)
{
    uint8_t r = data[0];
    uint8_t g = data[1];
    uint8_t b = data[2];
    set_color(strip1, r, g, b);
    set_color(strip2, r, g, b);    
    strip1.show();
}


void setup()
{ 
  Serial.begin(9600);
  xbee.setSerial( Serial );
  
  // setup light client commands
  relay.map_command( CMD_CONTROL_LIGHT, on_control_command );
  
  // initially off
  set_color( strip1, 0, 0, 0 );
  set_color( strip2, 0, 0, 0 );  
  strip1.show();
  strip2.show();
}

void loop()
{
    relay.read_packet( xbee );
}
