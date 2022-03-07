#pragma once

#ifndef OWL_COLOR_H
#define OWL_COLOR_H

#include <iostream>
#include <string>
#include <sstream>

namespace owl::color {
    struct RGB { 
        int r, g, b; 
        RGB(int r, int g, int b) : r(r), g(g), b(b) {}
    };

    inline RGB toRGB(std::string hex) {
        int r, g, b;
        std::sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
        return RGB(r, g, b);
    }

    inline std::string toHEX(RGB color) {
        std::stringstream ss;
        ss << "#" << std::hex << (color.r << 16 | color.g << 8 | color.b);
        return ss.str();
    }

    inline RGB interpolate(RGB a, RGB b, double t) {
        return RGB(a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t);
    }
}

#endif