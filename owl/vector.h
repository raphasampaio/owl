#pragma once

#ifndef OWL_VECTOR_H
#define OWL_VECTOR_H

#include <unordered_set>
#include <vector>

namespace owl::vector {
    template <typename type> inline void remove_duplicates(std::vector<type>& v) {
        std::unordered_set<type> seen;

        auto new_end = std::remove_if(v.begin(), v.end(), [&seen](const type& value) {
            if (seen.find(value) != std::end(seen)) {
                return true;
            }

            seen.insert(value);
            return false;
        });

        v.erase(new_end, v.end());
    }
}

#endif