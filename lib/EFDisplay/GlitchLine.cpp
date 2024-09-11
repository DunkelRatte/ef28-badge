#include "GlitchLine.h"
#include <Arduino.h>


GlitchLine::GlitchLine() {
    frame = 0;
    position = 0;
    direction = (random(10)%2==0)? 1 : -1;
    speed = random(1,5);
    thickness = random(1,3);
}

void GlitchLine::tick() {
    frame++;
    if (frame % speed == 0) {
        position++;
    }
}

bool GlitchLine::isFinished() {
    if(position > 127) {
        return true;
    }
    return false;
}

int GlitchLine::getPosition() {
    if(direction > 0) {
        return position;
    }else{
        return 127 - position;
    }
}

int GlitchLine::getTick() {
    return frame;
}

int GlitchLine::getThickness() {
    return thickness;
}
