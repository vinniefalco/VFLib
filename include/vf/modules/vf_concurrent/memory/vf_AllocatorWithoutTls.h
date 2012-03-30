// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file LICENSE.txt for licensing information.

#ifndef __VF_ALLOCATORWITHOUTTLS_VFHEADER__
#define __VF_ALLOCATORWITHOUTTLS_VFHEADER__

#include "vf/modules/vf_concurrent/memory/vf_PageAllocator.h"

// Lock-free Allocator that doesn't use thread local storage.
// This implementation is here in case a problem is found with
// the use of thread local storage.
//
class AllocatorWithoutTls
{
public:
  explicit AllocatorWithoutTls ();
  ~AllocatorWithoutTls ();

  void* allocate (const size_t bytes);
  static void deallocate (void* const p);

private:
  struct Header;

  class Block;

  inline Block* newBlock ();
  static inline void deleteBlock (Block* b);

private:
  Block* volatile m_active;
  GlobalPageAllocator::Ptr m_pages;
};

#endif
