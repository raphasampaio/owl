#pragma once

#ifndef OWL_HASH_H
#define OWL_HASH_H

#include <string>

namespace std {
    template <> struct hash<std::pair<std::string, std::string>> {
        inline size_t operator()(const std::pair<std::string, std::string>& v) const {
            std::hash<std::string> string_hasher;
            return string_hasher(v.first) ^ string_hasher(v.second);
        }
    };

    template <> struct hash<std::pair<int, int>> {
        inline size_t operator()(const std::pair<int, int>& v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

#endif