/*============================================================================*/
//
// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file GNU_GPL_v2.txt for full licensing terms.
// 
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
// 
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
// 
/*============================================================================*/

/** Include this to get the @ref vf_core module.

    @file vf_core.h
    @ingroup vf_core
*/

#ifndef VF_CORE_VFHEADER
#define VF_CORE_VFHEADER

/*============================================================================*/
/**
    @mainpage VFLib: A multipurpose class library built on JUCE.

    @details

    VFLib is a source code collection of individual modules containing
    functionality for a variety of applications. 

    VFLib requires JUCE (Jules' Utility Class Extensions) available from
    http://rawmaterialsoftware.com/juce.php. JUCE is available under both the
    GNU General Public License and a commercial, closed source license. Visit
    http://rawmaterialsoftware.com/jucelicense.php for more details.

    Other than JUCE, VFLib has no external dependencies.

    ## Platforms

    All platforms supported by JUCE are also supported by VFLib. Currently these
    platforms include:
  
    - Windows: Applications and VST/RTAS/NPAPI/ActiveX plugins can be built 
      using MS Visual Studio. The results are all fully compatible with Windows
      XP, Vista or Win7

    - Mac OS X: Applications and VST/AudioUnit/RTAS/NPAPI plugins with Xcode

    - GNU/Linux: Applications and plugins can be built for any kernel 2.6 or later.

    - iOS: Native iPhone and iPad apps

    - Android

    ## Prerequisites

    The documentation for VFLib assumes that the reader has a working knowledge
    of JUCE. Some modules built on external libraries assume that the reader
    understands the operation of those external libraries. Certain modules assume
    that the reader understands additional domain-specific information. Modules
    with additional prerequisites are marked in the documentation.

    ## External Modules

    Some modules bring in functionality provided by external libraries. For
    example, the \ref vf_bzip2 module provides the compression and decompression
    algorithms in bZip2. Usage of these external library modules is optional.
    They come with complete source code, as well as options for using either
    system or user provided variants of the external libraries: it is not
    necessary to download additional files to use these modules.

    External code incorporated into VFLib is covered by a separate license.
    See the licensing information and notes in the corresponding source files,
    for copyright information and terms of use.

    ## Integration

    VFLib requires recent versions of JUCE. It won't work with JUCE versions
    1.53 or earlier. To use the library it is necessary to first download JUCE to
    a location where VFLib can find it. Or, you can use your existing installation
    of JUCE. 

    This library uses the same modularized organizational structure as JUCE. To
    use a module, first add a path to the list of includes searched by your
    development environment or project, which points to the VFLib directory
    named "include". Then, add the single corresponding .c or .cpp file
    to your existing project which already uses JUCE. For example, to use the
    \ref vf_core module, add the file vf_core.cpp to your project. Some modules
    depend on other modules. All modules depend on \ref vf_core.

    To use a module, include the appropriate header from within your source code.
    For example, to access classes in the \ref vf_concurrent module, use this:

    @code
    #include "vf/modules/vf_concurrent/vf_concurrent.h"
    @endcode

    ## AppConfig

    ## References

    ##Location

    VFLib is hosted on github, at https://github.com/vinniefalco/VFLib

    @section License

    Copyright (C) 2008 by Vinnie Falco.

    Unless otherwise marked, files in VFLib are published under the [GNU General
    Public License, Version 2][01].  This program is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    Some files contain portions of these external projects, licensed separately:

    ### [bZip2][1]

    [bZip2][1] is Copyright (C) 1996-2010 Julian R Seward. All rights reserved. See
    the corresponding file LICENSE for licensing terms.

    ### [FreeType][2]

    Portions of the software are Copyright © 1996-2001, 2006 by
    [The FreeType Project][2]. All rights reserved. [FreeType][2] is distributed
    under both the [GNU General Public License, Version 2][01], or the
    [FreeType License][02].

    ### [JUCE][3]

    This software uses [JUCE][3], which is available under the [GNU General Public
    License][01]. [Commercial licenses][9] are also available.

    ### [Lua][4]

    Portions of this software are Copyright © 1994–2012 [Lua.org][4], PUC-Rio. Lua
    is distributed under the terms of the [MIT License][03].

    ### [Luabridge][5]

    [Luabridge][5] is Copyrighted (C) 2007 by Nathan Reed. [Luabridge][5] is
    distributed under the terms of the [BSD 3-Clause License][04].

    ### [Soci][6]

    [Soci][6] is Copyright (C) 2004-2008 Maciej Sobczak, Stephen Hutton, and
    various others noted in the corresponding source files. Soci is distributed
    under the [Boost Software License, Version 1.0][05].

    ### [SQLite][7]

    [SQLite][7] has been placed in the public domain.

    ### [TagLib][8]

    [TagLib][8] is distributed under both the [GNU Lesser General Public License,
    Version 2.1][06] and the [Mozilla Public License][07].

    [0]: http://vinniefalco.github.com/VFLib/ "VFLib Documentation"

    [1]: http://www.bzip.org/ "bZip2: Home"
    [2]: http://freetype.org/ "The FreeType Project"
    [3]: http://rawmaterialsoftware.com/juce.php "JUCE"
    [4]: http://www.lua.org/ "The Programming Language Lua"
    [5]: http://sourceforge.net/projects/luabridge/ "luabridge"
    [6]: http://soci.sourceforge.net/ "SOCI"
    [7]: http://sqlite.org/ "SQLite Home Page"
    [8]: http://developer.kde.org/~wheeler/taglib.html "TagLib"
    [9]: http://rawmaterialsoftware.com/jucelicense.php "JUCE Commercial Licensing"

    [01]: http://www.gnu.org/licenses/gpl-2.0.html "GNU General Public License, version 2"
    [02]: http://www.freetype.org/FTL.TXT "The FreeType Project License"
    [03]: http://www.opensource.org/licenses/mit-license.html "The MIT License"
    [04]: http://www.opensource.org/licenses/BSD-3-Clause "BSD 3-Clause License"
    [05]: http://www.boost.org/LICENSE_1_0.txt "Boost Software License, Version 1.0"
    [06]: http://www.gnu.org/licenses/lgpl-2.1.html "Gnu Lesser General Public License, version 2.1"
    [07]: http://www.mozilla.org/MPL/1.1/ "Mozilla Public License"

    @author <a href="http://vinniefalco.com">Vinnie Falco</a>
    @version 0.1
    @date 2008-2012
    @copyright Copyright (C) 2008 by Vinnie Falco.
    @copyright Provided by the GNU General Public License, Version 2
*/

/*============================================================================*/
/**
  @internal

  Implementation classes.

  Thase classes are used internally.

  @defgroup internal internal
*/
/*============================================================================*/
/**
  External modules.

  These modules bring in functionality from third party or system libraries.

  @defgroup external external
*/
/*============================================================================*/
/**
  Core classes.

  This module provides core required functionality, and classes useful for
  general development. All other modules require this module.

  @todo Discuss the treatment of exceptions versus Error objects in the library.

  @todo Discuss the additions to AppConfig.h

  @defgroup vf_core vf_core
*/

/*  See the Juce notes regarding AppConfig.h

    This file must always be included before any Juce headers.

    There are some VFLib specific build options that may be placed
    into this file. See the AppConfig.h provided with VFLib.
*/
#include "AppConfig.h"

#ifndef VF_USE_BOOST
#define VF_USE_BOOST      0
#endif

#ifndef VF_USE_BZIP2
#define VF_USE_BZIP2      0
#endif

#ifndef VF_USE_FREETYPE
#define VF_USE_FREETYPE   0
#endif

// Handy macro that lets pragma warnings be clicked in the output window
// Usage: #pragma message(VF_LOC_"Advertise here!")
#define VF_STR2_(x) #x
#define VF_STR1_(x) VF_STR2_(x)
#define VF_LOC_ __FILE__ "("VF_STR1_(__LINE__)") : WARNING: "

// Turns vflib specific debugging support on or off
//
#ifndef VF_DEBUG
#define VF_DEBUG JUCE_DEBUG // get the flag from Juce
#endif

// Enables leak checking
//
#ifndef VF_CHECK_LEAKS
#define VF_CHECK_LEAKS JUCE_CHECK_MEMORY_LEAKS
#endif

// Includes Juce

#ifdef _CRTDBG_MAP_ALLOC
#error "MSVC C Runtime Debug Macros not supported"
#endif

// If the MSVC debug heap headers were included, disable
// the macros during the juce include since they conflict.
#ifdef _CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
  #include <stdlib.h>
  #include <malloc.h>

  #pragma push_macro("calloc")
  #pragma push_macro("free")
  #pragma push_macro("malloc")
  #pragma push_macro("realloc")
  #pragma push_macro("_recalloc")
  #pragma push_macro("_aligned_free")
  #pragma push_macro("_aligned_malloc")
  #pragma push_macro("_aligned_offset_malloc")
  #pragma push_macro("_aligned_realloc")
  #pragma push_macro("_aligned_recalloc")
  #pragma push_macro("_aligned_offset_realloc")
  #pragma push_macro("_aligned_offset_recalloc")
  #pragma push_macro("_aligned_msize")

  #undef calloc
  #undef free
  #undef malloc
  #undef realloc
  #undef _recalloc
  #undef _aligned_free
  #undef _aligned_malloc
  #undef _aligned_offset_malloc
  #undef _aligned_realloc
  #undef _aligned_recalloc
  #undef _aligned_offset_realloc
  #undef _aligned_offset_recalloc
  #undef _aligned_msize
#endif

#include "modules/juce_core/juce_core.h"

#ifdef _CRTDBG_MAP_ALLOC
  #pragma pop_macro("_aligned_msize")
  #pragma pop_macro("_aligned_offset_recalloc")
  #pragma pop_macro("_aligned_offset_realloc")
  #pragma pop_macro("_aligned_recalloc")
  #pragma pop_macro("_aligned_realloc")
  #pragma pop_macro("_aligned_offset_malloc")
  #pragma pop_macro("_aligned_malloc")
  #pragma pop_macro("_aligned_free")
  #pragma pop_macro("_recalloc")
  #pragma pop_macro("realloc")
  #pragma pop_macro("malloc")
  #pragma pop_macro("free")
  #pragma pop_macro("calloc")
#endif

using juce::int64;
using juce::uint64;
using juce::uint32;
using juce::uint8;

#ifndef VF_USE_BOOST
#define VF_USE_BOOST 0
#endif

#if VF_USE_BOOST
#include <boost/thread/tss.hpp>
#endif

#if JUCE_MSVC
#include <crtdbg.h>
#include <functional>
#endif

#if JUCE_IOS || JUCE_MAC
#if VF_USE_BOOST
#include <boost/bind.hpp>
#include <boost/function.hpp>
#else
#include <tr1/functional>
#endif
#endif

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <exception>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <new>
#include <numeric>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <locale.h>
#include <math.h>
#include <memory.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace vf
{

using namespace juce;

#define vfassert jassert

}

namespace vf
{

#include "memory/vf_Uncopyable.h"

#include "containers/vf_LockFreeStack.h"
#include "containers/vf_LockFreeQueue.h"
#include "containers/vf_List.h"

#include "diagnostic/vf_CatchAny.h"
#include "diagnostic/vf_Debug.h"
#include "diagnostic/vf_Error.h"
#include "diagnostic/vf_FPUFlags.h"
#include "diagnostic/vf_LeakChecked.h"
#include "diagnostic/vf_SafeBool.h"
#include "diagnostic/vf_Throw.h"

#include "events/vf_OncePerSecond.h"
#include "events/vf_PerformedAtExit.h"

#include "functor/vf_Bind.h"
#include "functor/vf_Function.h"

#include "math/vf_Interval.h"
#include "math/vf_Math.h"
#include "math/vf_MurmurHash.h"

#include "memory/vf_AtomicCounter.h"
#include "memory/vf_AtomicFlag.h"
#include "memory/vf_AtomicPointer.h"
#include "memory/vf_AtomicState.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#pragma warning (disable: 4355) // 'this' used in base member
#endif
#include "memory/vf_CacheLine.h"
#if JUCE_MSVC
#pragma warning (pop)
#endif

#include "memory/vf_MemoryAlignment.h"
#include "memory/vf_ReferenceCountedSingleton.h"
#include "memory/vf_StaticObject.h"

#include "threads/vf_SpinDelay.h"
#include "threads/vf_InterruptibleThread.h"

}

#endif

