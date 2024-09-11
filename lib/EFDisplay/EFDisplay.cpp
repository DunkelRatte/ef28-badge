// MIT License
//
// Copyright 2024 Eurofurence e.V. 
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the “Software”),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

/**
 * @author Irah / DarkRat
 */

#include <vector>
#include <EFLogging.h>
#include <EFBoard.h>
#include <EFLed.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <GlitchLine.h>

#include "EFDisplay.h"

#define OLED_CS    5   // Chip Select
#define OLED_DC    6   // Data/Command
#define OLED_RESET 7   // Reset
#define OLED_MOSI  17  // MOSI
#define OLED_SCLK  18  // SCLK


static uint16_t counter = 0;
static bool glitch_anim = false;
static int thick_line = -1;
static int thin_line = -1;

std::vector<GlitchLine*> lines = {};

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET);

void EFDisplayClass::init() {
    SPI.begin(OLED_SCLK, -1, OLED_MOSI, OLED_CS);
    u8g2.begin();
    u8g2.setDisplayRotation(U8G2_R3);
    u8g2.clearBuffer();
    LOG_INFO("Display setup!");
}

void EFDisplayClass::loop() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x8_tr);


    animationTick();

    EFLed.setDragonEye(CRGB(60, 60, 100));
    EFLed.setDragonMuzzle(CRGB(40, 40, 80));


    String batt = "BAT:" + String(EFBoard.getBatteryCapacityPercent()) + "%";

    if(!EFBoard.isBatteryPowered()) {
        batt = "USB POWER";
    }
    u8g2.drawStr(10, 10, batt.c_str());
//    u8g2.drawStr(10, 20, ("PWR:" + String(EFBoard.getBatteryVoltage()) + "V").c_str());

    if(random(0, 1000) == 0) {
        lines.insert(lines.end(), new GlitchLine());
    }

    animateGlitchLines();

    eyeOutline();

    drawTraces();

    u8g2.sendBuffer();
}

void EFDisplayClass::animateGlitchLines() const {
    for(auto line: lines) {
        if(!line->isFinished()) {
            line->tick();
            for(int i = 0; i < line->getThickness();i++) {
                u8g2.drawLine(0, line->getPosition() + i , 63, line->getPosition() + i);
            }
        }
    }
}

void EFDisplayClass::drawTraces() const {
    const int offset[] = {6, 87};
    const std::vector<std::array<int, 2>> points = {
            {0, 0},
            {7, 7},
            {47, 7},
            {54, 0},
    };
    drawShape(offset, points);

    const std::vector<std::array<int, 2>> points2 = {
            {18, 7},
            {5, 20},
            {5, 34},
            {10, 39},
            {16, 39},
            {24, 31},
    };
    drawShape(offset, points2);

    const std::vector<std::array<int, 2>> points3 = {
            {32, 7},
            {47, 22},
            {47, 34},
            {52, 39},
    };
    drawShape(offset, points3);

    const std::vector<std::array<int, 2>> points4 = {
            {5, 34},
            {5, 44},
    };
    drawShape(offset, points4);
}

void EFDisplayClass::drawShape(const int *offset, const std::vector<std::array<int, 2>> &points) const {
    for(int i = 0; i < points.size() - 1; i++){
        auto p = points[i];
        auto in = points[i + 1];
        u8g2.drawLine(p[0] + offset[0], p[1] + offset[1], in[0] + offset[0], in[1] + offset[1]);
    }
}

void EFDisplayClass::eyeOutline() const {
    int point_size = 5;
    int8_t points[5][2] = {
            {0, 0},
            {17, 17},
            {3, 31},
            {-25, 31},
            {-25, 21},
    };

    int x_offset = 43;
    int y_offset = 42;
    for(int p=0; p < point_size; p++){
        int in = (p + 1) % point_size;
        u8g2.drawLine(points[p][0] + x_offset, points[p][1] + y_offset, points[in][0] + x_offset, points[in][1] + y_offset);
    }
}

void EFDisplayClass::animationTick() const {
    counter++;
    if(counter > 1000) counter = 0;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EFDISPLAY)
EFDisplayClass EFDisplay;
#endif