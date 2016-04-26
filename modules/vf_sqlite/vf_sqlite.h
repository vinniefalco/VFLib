/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

/** Include this to get the @ref vf_sqlite external module.

    @file vf_sqlite.h
    @ingroup vf_sqlite external
*/

#ifndef VF_SQLITE_VFHEADER
#define VF_SQLITE_VFHEADER

#include "juce_core/system/juce_TargetPlatform.h"

/*============================================================================*/
/** 
  A self-contained, serverless, zero configuration, transactional
  SQL engine.

  This external module provides the SQLite embedded database library.

  SQLite is public domain software, visit http://sqlite.org

  @note To control the use of the native SQLite library on supported platforms,
        see AppConfig.h.

  @defgroup vf_sqlite vf_sqlite
  @ingroup external
*/

#if JUCE_MSVC
    #pragma warning (push)
    #pragma warning (disable: 4100)
    #pragma warning (disable: 4306)
    #pragma warning (disable: 4456)
#endif

#if JUCE_IOS || JUCE_MAC
    #define VF_HAVE_NATIVE_SQLITE 1
#else
    #define VF_HAVE_NATIVE_SQLITE 0
#endif

#ifndef VF_SQLITE_PRIVATE_INTERFACE
    #if VF_USE_NATIVE_SQLITE && VF_HAVE_NATIVE_SQLITE
        #include <sqlite3.h>
    #else
        #include "sqlite/sqlite3.h" // Amalgamated
    #endif
#endif

#if JUCE_MSVC
    #pragma warning (pop)
#endif

#endif //VF_SQLITE_VFHEADER
