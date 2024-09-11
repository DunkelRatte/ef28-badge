#ifndef EFDISPLAY_H_
#define EFDISPLAY_H_

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

class EFDisplayClass {

    public:

        void init();
        void loop();

    void animationTick() const;

    void animThickLine() const;

    void animThinLine() const;

    void eyeOutline() const;

    void drawShape(const int *offset, const std::vector<std::array<int, 2>> &points) const;

    void drawTraces() const;

    void animateGlitchLines() const;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EFDISPLAY)
extern EFDisplayClass EFDisplay;
#endif

#endif /* EFDISPLAY_H_ */
