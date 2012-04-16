// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file README.md for licensing information.

#ifndef __VF_STATIC_VFHEADER__
#define __VF_STATIC_VFHEADER__

#include "vf_UiBase.h"

// A Static control has no interaction, just drawing.
// Child components can be added to the ResizableLayout.
//

namespace Facade {

class Static : public ConnectedEdges
{
public:
};

class SolidColour : public Static
{
public:
  SolidColour ();
  void setSolidColour (Colour const& colour);
  void paint (Graphics& g, Rectangle <int> const& bounds);

private:
  Colour m_colour;
};

}

namespace Control {

class Static
  : public Component
  , public ResizableLayout
  , public Base
{
public:
  Static ();

  int getConnectedEdgeFlags () const
    { return m_connectedEdgeFlags; }

  void setConnectedEdges (int flags);

  void setConnectedEdgeFlag (int flag, bool connected)
  {
    if (connected)
      setConnectedEdges (getConnectedEdgeFlags () | flag);
    else
      setConnectedEdges (getConnectedEdgeFlags () & ~flag);
  }

  void setConnectedOnLeft (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnLeft, connected); }

  void setConnectedOnRight (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnRight, connected); }

  void setConnectedOnTop (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnTop, connected); }

  void setConnectedOnBottom (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnBottom, connected); }

  void paint (Graphics& g);
  void paintOverChildren (Graphics& g);

protected:
  virtual void updateFacade ();

private:
  int m_connectedEdgeFlags;
};

template <class FacadeType>
class StaticType : public Static, public FacadeType
{
public:
};

}

#endif