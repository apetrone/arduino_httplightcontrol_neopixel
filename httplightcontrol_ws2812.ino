#include <XBee.h>

// Designed for use with an Arduino Pro Mini 5v

#include "wirelessclient.h"
#include <Adafruit_NeoPixel.h>

XBee xbee = XBee();

const uint8_t NUM_LEDS = 30;
const uint8_t DATA_PIN1 = 13;
const uint8_t DATA_PIN2 = 12;

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
    
    // for now, we're going to hard code on/off
    if (data[0] == 0)
    {
      r = g = b = 0;
    }
    else
    {
      r = g = b = 255;
    }
    
    
    set_color(strip1, r, g, b);
    set_color(strip2, r, g, b);    
    strip1.show();
    strip2.show();
}


void setup()
{ 
  // set timer1 to default value
  TCCR1B = TCCR1B & (0b11111000 | 0x03);

  // set timer2 to default value
  TCCR2B = TCCR2B & (0b11111000 | 0x04);  
  
  Serial.begin(9600);
  xbee.setSerial( Serial );
  
  // setup light client commands
  relay.map_command( CMD_CONTROL_LIGHT, on_control_command );
  
  strip1.begin();
  strip2.begin();
  
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
