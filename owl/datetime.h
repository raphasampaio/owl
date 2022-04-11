#pragma once

#ifndef OWL_DATETIME_H
#define OWL_DATETIME_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <limits>

namespace owl::datetime {
    inline bool is_leap_year(int year) {
        if ((year & 3) != 0) return false;
        return ((year % 100) != 0 || (year % 400) == 0);
    }

    inline int year_to_decade(int year) {
        return year - (year % 10);
    }
}

#endif