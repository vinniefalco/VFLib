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

#ifndef VF_XYZCOLOUR_VFHEADER
#define VF_XYZCOLOUR_VFHEADER

class XYZColour
{
public:
  XYZColour ();
  XYZColour (float x, float y, float z);
  XYZColour (float x, float y, float z, float alpha);
  XYZColour (XYZColour const& xyz);
  XYZColour (VF_JUCE::Colour const& sRGB);

  XYZColour& operator= (XYZColour const& other);

  float getX () const { return m_x; }
  float getY () const { return m_y; }
  float getZ () const { return m_z; }
  float getAlpha () const { return m_alpha; }

  VF_JUCE::Colour const toRGB () const;

private:
  static XYZColour const from (VF_JUCE::Colour const& sRGB);

private:
  float m_x;
  float m_y;
  float m_z;
  float m_alpha;
};

#endif