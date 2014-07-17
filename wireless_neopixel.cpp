// -------------------------------------------------------------
// Copyright 2012- (C) Adam Petrone

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM,OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------
#include "wireless_neopixel.h"
#include <Adafruit_NeoPixel.h>

//
// WirelessNeoPixel
WirelessNeoPixel::WirelessNeoPixel( Adafruit_NeoPixel * in_strip )
{
	strip = in_strip;
	if ( strip )
	{
		strip->begin();
	}

	current_color = 1;

	color_table[0] = strip->Color( 0, 0, 0 );
	color_table[1] = strip->Color( 127, 0, 0 );
	color_table[2] = strip->Color( 127, 0, 127 );
	color_table[3] = strip->Color( 127, 35, 0 );
	color_table[4] = strip->Color( 0, 127, 0 );
	color_table[5] = strip->Color( 0, 127, 127 );
	color_table[6] = strip->Color( 0, 0, 127 );
	color_table[7] = strip->Color( 127, 127, 127 );
    transition_time = 0;
    transition_current = 0;
} // WirelessNeoPixel

WirelessNeoPixel::~WirelessNeoPixel()
{

} // ~WirelessNeoPixel

void WirelessNeoPixel::set_color( uint8_t color_index )
{
	current_color = color_index;

} // set_color


void WirelessNeoPixel::transition_color( uint8_t color_index, uint16_t time )
{
    transition_current = 0;
    transition_time = time;
    
    color_index = color_index & (MAX_COLORS-1);
    target_color = color_index;
} // transition_color

void WirelessNeoPixel::show()
{
    uint32_t current = color_table[ current_color ];
    uint32_t target = color_table[ target_color ];
    uint8_t a[3];
    uint8_t b[3];
    uint8_t c[3];
    
	if ( strip )
	{
              if ( current_color != target_color )
              {
                a[0] = (current >> 8) | 0x80;
                a[1] = (current >> 16) | 0x80;
                a[2] = (current | 0x80);
                
                b[0] = (target >> 8) | 0x80;
                b[1] = (target >> 16) | 0x80;
                b[2] = (target | 0x80);
                float t = (transition_current/(float)transition_time);
                c[0] = a[0] + t * (b[0] - a[0]);
                c[1] = a[1] + t * (b[1] - a[1]);
                c[2] = a[2] + t * (b[2] - a[2]);
                ++transition_current;
              
              
                if ( transition_current >= transition_time )
                {
                  transition_current = 0;
                  current_color = target_color;
                  
                  // uncomment the next line to debug transitions and color changes
                  //transition_color( current_color+1, 100 );
                }
              
              }
              else
              {
              c[0] = (current >> 8) | 0x80;
              c[1] = (current >> 16) | 0x80;
              c[2] = (current | 0x80);                
              }
              
		for( int i = 0; i < strip->numPixels(); ++i )
		{
			strip->setPixelColor( i, strip->Color(c[0], c[1], c[2]) );
		}

		strip->show();
	}
} // show

