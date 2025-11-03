/*---------------------------------------------------------*\
||| debugutil.h                                             |
|||                                                         |
|||   Debug utility for conditional logging                |
|||   Checks QSettings to determine if debug mode is on    |
|||                                                         |
|||   This file is part of the LL-Connect 3 project        |
|||   SPDX-License-Identifier: GPL-2.0-or-later            |
\*---------------------------------------------------------*/

#pragma once

#include <cstdio>

namespace DebugUtil {

// Check if debug mode is enabled (implemented in debugutil.cpp)
bool isDebugEnabled();

// Debug printf (only prints if debug mode is enabled)
template<typename... Args>
inline void debugPrintf(const char* format, Args... args) {
    if (isDebugEnabled()) {
        printf(format, args...);
    }
}

} // namespace DebugUtil

// Convenience macros
#define DEBUG_PRINTF(...) DebugUtil::debugPrintf(__VA_ARGS__)

