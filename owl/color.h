#pragma once

#ifndef OWL_COLOR_H
#define OWL_COLOR_H

#include <iostream>
#include <string>
#include <sstream>

namespace owl::color {
    struct Color { 
        int r, g, b; 
        Color(int r, int g, int b) : r(r), g(g), b(b) {}
    };

    inline Color toRGB(std::string hex) {
        int r, g, b;
        std::sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
        return Color(r, g, b);
    }

    inline std::string toHEX(Color color) {
        char hex_color[8];
        std::snprintf(hex_color, sizeof hex_color, "#%02x%02x%02x", color.r, color.g, color.b);
        return std::string(hex_color);
    }

    inline Color interpolate(Color a, Color b, double t) {
        return Color(
            a.r + (b.r - a.r) * t, 
            a.g + (b.g - a.g) * t, 
            a.b + (b.b - a.b) * t
        );
    }
}

#endif