#pragma once

#ifndef OWL_ALGORITHM_H
#define OWL_ALGORITHM_H

#include <vector>

namespace owl::algorithm {
    inline bool all_true(std::vector<bool>& v) {
        for (auto i : v) { if (!i) { return false; } }
        return true;
    }

    inline bool all_false(std::vector<bool>& v) {
        for (auto i : v) { if (i) { return false; } }
        return true;
    }
}

#endif