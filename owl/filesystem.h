#pragma once

#ifndef OWL_FILESYSTEM_H
#define OWL_FILESYSTEM_H

#include <string>

namespace owl::filesystem {
    const std::string SEPARATOR =
#ifdef _WIN32
        "\\";
#else
        "/";
#endif
}

#endif