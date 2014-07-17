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
#pragma once

#include <Arduino.h> // for uint8_t
#include "wirelessclient.h"

const uint8_t COLOR_TRANSITION_TIME = 100;
const uint16_t MAX_COLORS = 8;
class Adafruit_NeoPixel;

struct WirelessNeoPixel : public WirelessClient
{
	Adafruit_NeoPixel * strip;
	uint32_t color_table[ MAX_COLORS ];
	uint8_t current_color;
        uint8_t target_color;
        uint16_t transition_time;
        uint16_t transition_current;

	WirelessNeoPixel( Adafruit_NeoPixel * strip );
	~WirelessNeoPixel();
	
	void set_color( uint8_t color_index );
        void transition_color( uint8_t color_index, uint16_t transition_time );
	void show();
}; // WirelessLPD8806
