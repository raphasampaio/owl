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
}

#endif