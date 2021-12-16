#pragma once

#ifndef OWL_CONVERT_H
#define OWL_CONVERT_H

#include <owl/constant.h>

namespace owl::convert {
    inline double MWtoPU(double value) {
        return value / 100.0;
    }

    inline double PUtoMW(double value) {
        return value * 100.0;
    }

    inline double degreeToRadian(double value) {
        return (value * owl::constant::pi) / 180;
    }
}

#endif