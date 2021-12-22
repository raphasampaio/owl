#pragma once

#ifndef OWL_MEMORY_H
#define OWL_MEMORY_H

#ifdef _WIN32
#include <windows.h>
#else
#endif

namespace owl::memory {
    inline unsigned long load() {
#ifdef _WIN32
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
        return statex.dwMemoryLoad;
#else
#endif
    }
}

#endif