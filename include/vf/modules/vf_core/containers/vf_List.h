//==============================================================================
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
//==============================================================================

#ifndef VF_LIST_VFHEADER
#define VF_LIST_VFHEADER

#include "../diagnostic/vf_Error.h"
#include "../diagnostic/vf_Throw.h"

//==============================================================================
/**
    Intrusive doubly linked list.

    The intrusive List is container similar in operation to std::list in the
    Standard Template Library (STL). Intrusive containers are special containers
    that offer better performance and exception safety guarantees than
    non-intrusive containers (like the STL containers). They are useful building
    blocks for high performance concurrent systems or other purposes where
    allocations are restricted (such as the audioDeviceIOCallback), because
    intrusive list operations do not allocate or free memory.

    While intrusive containers were and are widely used in C, they became more
    and more forgotten in C++ due to the presence of the standard containers
    which don't support intrusive techniques. List not only reintroduces this
    technique to C++ for doubly linked lists, but also encapsulates the
    implementation in a mostly compliant STL interface. Hence anyone familiar
    with standard containers can easily use it.

    To use the list, we first derive the object we want to place into the list
    from List::Node:

    @code

    struct Object : List <Object>::Node
    {
      Object (int value) : m_value (value)
      {
      }
      
      int m_value;
    };

    @endcode

    Now we declare the list, and add a couple of items.

    @code

    List <Object> list;

    list.push_back (* (new Object (1)));
    list.push_back (* (new Object (2)));

    @endcode

    For compatibility with the standard containers, push_back() expects
    a reference to the object. Unlike the standard container, however,
    push_back() places the actual object in the list and not a copy-constructed
    duplicate.

    Iterating over the list follows the same idiom as the STL:

    @code

    for (List <Object>::iterator iter = list.begin();
         iter != list.end;
         ++iter)
      std::cout << iter->m_value;

    @endcode

    You can even use BOOST_FOREACH, or range based for loops:

    @code

    BOOST_FOREACH (Object& object, list)  // boost only
      std::cout << object.m_value;

    for (Object& object : list)           // c++11 only
      std::cout << object.m_value;

    @endcode

    Because List is mostly STL compliant, it can be passed into STL algorithms:
    e.g. std::for_each() or std::find_first_of.

    In general, objects placed into a List should be dynamically allocated
    although this cannot be enforced at compile time. Since the caller provides
    the storage for the object, the caller is also responsible for deleting the
    object. An object still exists after being removed from a List, until the
    caller deletes it. This means an element can be moved from one List to
    another with practically no overhead.

    Unlike the standard containers, an object may only exist in one list at a
    time, unless special preparations are made. The Tag template parameter is
    used to distinguish between different list types for the same object,
    allowing the object to exist in more than one list simultaneously.

    For example, consider an actor system where a global list of actors is
    maintained, so that they can each be periodically receive processing
    time. We wish to also maintain a list of the subset of actors that require
    a domain-dependent update. To achieve this, we declare two tags, the
    associated list types, and the list element thusly:

    @code

    struct Actor;         // Forward declaration required

    struct ProcessTag { };
    struct UpdateTag { };

    typedef List <Actor, ProcessTag> ProcessList;
    typedef List <Actor, UpdateTag> UpdateList;

    // Derive from both node types so we can be in each list at once.
    //
    struct Actor : ProcessList::Node, UpdateList::Node
    {
      bool process ();    // returns true if we need an update
      void update ();
    };

    @endcode

    @param Tag  A type name used to distinguish lists and nodes, for
                putting objects in multiple lists. If this parameter is
                omitted, the default tag is used.

    @ingroup vf_core
*/

struct ListDefaultTag { };

template <class Element, class Tag = ListDefaultTag>
class List : Uncopyable
{
public:
  typedef int size_type;

  typedef Element        value_type;
  typedef Element&       reference;
  typedef Element const& const_reference;
  typedef Element*       pointer;
  typedef Element const* const_pointer;

  class Node : Uncopyable
  {
  public:
    Node () { }

  private:
    friend class List;
    Node* m_next;
    Node* m_prev;
  };

private:
  template <class ElemType, class NodeType>
  class iterator_base : public std::iterator <
	std::bidirectional_iterator_tag, int>
  {
  public:
	typedef Value value_type;
    typedef ElemType* pointer;
	typedef ElemType& reference;
	
    reference operator*() const
	{
	  return dereference ();
	}

    pointer operator->() const
	{
	  return &dereference ();
	}

	iterator_base& operator++()
	{
	  increment ();
	  return *this;
	}

	iterator_base operator++(int)
	{
	  iterator_base result (*this);
	  increment ();
	  return result;
	}

	iterator_base& operator--()
	{
	  decrement ();
	  return *this;
	}

    iterator_base operator--(int)
	{
	  iterator_base result (*this);
	  decrement ();
	  return result;
	}

  private:
    explicit iterator_base (NodeType* node) : m_node (node)
    {
    }

  public:
    iterator_base () : m_node (0)
    {
    }

    template <class OtherElemType, class OtherNodeType>
    iterator_base (iterator_base <OtherElemType, OtherNodeType> const& other)
      : m_node (other.m_node)
    {
    }

    template <class OtherElemType, class OtherNodeType>
    iterator_base& operator= (iterator_base <OtherElemType, OtherNodeType> const& other)
    {
      m_node = other.m_node;
      return *this;
    }

    template <class OtherElemType, class OtherNodeType>
    bool operator == (iterator_base <OtherElemType, OtherNodeType> const& other) const
    {
      return m_node == other.m_node;
    }

    template <class OtherElemType, class OtherNodeType>
    bool operator != (iterator_base <OtherElemType, OtherNodeType> const& other) const
    {
      return ! this->operator== (other);
    }
    
  private:
    friend class List;

    NodeType* get_node ()
    {
      return m_node;
    }

    NodeType const* get_node () const
    {
      return m_node;
    }

    reference dereference () const
    {
      return *static_cast <ElemType*> (m_node);
    }

    bool equal (NodeType *const *node) const
    {
      return m_node == node;
    }

    void increment ()
    {
      vfassert (m_node->m_next);
      m_node = m_node->m_next;
    }

    void decrement ()
    {
      vfassert (m_node->m_prev && m_node->m_prev->m_prev != 0);
      m_node = m_node->m_prev;
    }

  private:
    NodeType* m_node;
  };

public:
  typedef iterator_base <Element, Node> iterator;
  typedef iterator_base <Element const, Node const> const_iterator;

public:
  List () : m_size (0)
  {
    m_head.m_prev = nullptr; // identifies the head
    m_tail.m_next = nullptr; // identifies the tail
    clear ();
  }

  size_type size () const
  {
	return m_size;
  }

  reference front ()
  {
    if (empty ())
      Throw (Error().fail (__FILE__, __LINE__, Error::noMoreData));
    return element_from (m_head.m_next);
  }

  const_reference front () const
  {
    if (empty ())
      Throw (Error().fail (__FILE__, __LINE__, Error::noMoreData));
    return element_from (m_head.m_next);
  }

  reference back ()
  {
    if (empty ())
      Throw (Error().fail (__FILE__, __LINE__, Error::noMoreData));
    return element_from (m_tail.m_prev);
  }

  const_reference back () const
  {
    if (empty ())
      Throw (Error().fail (__FILE__, __LINE__, Error::noMoreData));
    return element_from (m_tail.m_prev);
  }

  iterator begin ()
  {
    return iterator (m_head.m_next);
  }

  const_iterator begin () const
  {
    return const_iterator (m_head.m_next);
  }

  const_iterator cbegin () const
  {
    return const_iterator (m_head.m_next);
  }

  iterator end ()
  {
    return iterator (&m_tail);
  }

  const_iterator end () const
  {
    return const_iterator (&m_tail);
  }

  const_iterator cend () const
  {
    return const_iterator (&m_tail);
  }

  bool empty () const
  {
    return m_head.m_next == &m_tail;
  }

  void clear ()
  {
    m_head.m_next = &m_tail;
    m_tail.m_prev = &m_head;
    m_size = 0;
  }

  iterator insert (iterator pos, Element& elem)
  {
    Node* node = node_from (elem);
    node->m_next = pos.get_node ();
    node->m_prev = node->m_next->m_prev;
    node->m_next->m_prev = node;
    node->m_prev->m_next = node;
    ++m_size;
    return iterator (node);
  }

  void insert (iterator pos, List& other)
  {
    if (!other.empty ())
    {
      Node* before = pos.get_node ();
      other.m_head.m_next->m_prev = before->m_prev;
      before->m_prev->m_next = other.m_head.m_next;
      other.m_tail.m_prev->m_next = before;
      before->m_prev = other.m_tail.m_prev;
      m_size += other.m_size;
      other.clear ();
    }
  }

  iterator erase (iterator pos)
  {
    Node* node = pos.get_node ();
    ++pos;
    node->m_next->m_prev = node->m_prev;
    node->m_prev->m_next = node->m_next;
    --m_size;
    return pos;
  }

  void push_front (Element& elem)
  {
    insert (begin(), elem);
  }

  void pop_front ()
  {
    if (empty ())
      Throw (Error().fail (__FILE__, __LINE__, Error::noMoreData));
    erase (begin ());
  }

  void push_back (Element& elem)
  {
    insert (end(), elem);
  }

  void pop_back ()
  {
    if (empty ())
      Throw (Error().fail (__FILE__, __LINE__, Error::noMoreData));
    erase (--end ());
  }

  void swap (List& other)
  {
    List temp;
    temp.append (other);
    other.append (*this);
    append (temp);
  }

  void prepend (List& list)
  {
    insert (begin (), list);
  }

  void append (List& list)
  {
    insert (end(), list);
  }

  iterator iterator_to (Element& elem) const
  {
    return iterator (static_cast <Node*> (&elem));
  }

  const_iterator const_iterator_to (Element const& elem) const
  {
    return const_iterator (static_cast <Node const*> (&elem));
  }

private:
  inline reference element_from (Node* node)
  {
    return *(static_cast <pointer> (node));
  }

  inline const_reference element_from (Node const* node) const
  {
    return *(static_cast <const_pointer> (node));
  }

  inline Node* node_from (Element& elem)
  {
    return static_cast <Node*> (&elem);
  }

  inline Node const* node_from (Element const& elem) const
  {
    return static_cast <Node const*> (&elem);
  }

private:
  size_type m_size;
  Node m_head;
  Node m_tail;
};

#endif
