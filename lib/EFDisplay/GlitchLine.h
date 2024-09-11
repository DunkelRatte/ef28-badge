#ifndef EF28_BADGE_GLITCHLINE_H
#define EF28_BADGE_GLITCHLINE_H


#include <vector>

class GlitchLine {

private:
    int frame;
    int speed;
    int position;
    int thickness;
    int direction{};

public:
    GlitchLine();

    void tick();

    int getPosition();

    int getThickness();

    int getTick();

    bool isFinished();
};


#endif //EF28_BADGE_GLITCHLINE_H
