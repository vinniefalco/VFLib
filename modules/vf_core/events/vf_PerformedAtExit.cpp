/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

class PerformedAtExit::Performer
{
public:
  typedef Static::Storage <LockFreeStack <PerformedAtExit>, PerformedAtExit> Stack;

private:
  ~Performer ()
  {
    PerformedAtExit* object = s_list->pop_front ();

    while (object != nullptr)
    {
      object->performAtExit ();

      object = s_list->pop_front ();
    }

    LeakCheckedBase::detectAllLeaks ();
  }

public:
  static void push_front (PerformedAtExit* object)
  {
    s_list->push_front (object);
  }

private:
  static Stack s_list;
  static Performer s_performer;
};

PerformedAtExit::Performer PerformedAtExit::Performer::s_performer;
PerformedAtExit::Performer::Stack PerformedAtExit::Performer::s_list;

PerformedAtExit::PerformedAtExit ()
{
#ifdef JUCE_IOS
  // TODO: PerformedAtExit::Performer::push_front crashes on iOS if s_storage is not accessed before used
  char *hack = PerformedAtExit::Performer::Stack::s_storage;
#endif
	
  Performer::push_front (this);
}

