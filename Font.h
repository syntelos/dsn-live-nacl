/*
 * DSN Live NaCl
 * Copyright (C) 2014, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _DSNL_FONT_H
#define _DSNL_FONT_H

#include "Fv3VertexArray.h"

/*!
 * Static glyph 
 */
struct FontGlyph {

    const float minX;
    const float midX;
    const float maxX;
    const float minY;
    const float midY;
    const float maxY;
    const float minZ;
    const float midZ;
    const float maxZ;
    const unsigned int length;  // length of vertices array (number of floats)
    const float* vertices;
};
/*!
 * Abstract base class for glyph sets.
 */
class Font {
 public:
    const float em;
    const float ascent;
    const float descent;
    const float leading;
    const GLushort mode;

    Font(float em, float ascent, float descent, float leading, GLushort mode);
    virtual ~Font();

    /*!
     * Returns 0 for glyph unavailable and space character.  The width
     * of a space is one em.
     */
    virtual const FontGlyph* get(char) const = 0;
};
/*!
 * Glyph string
 */
class FontGlyphVector : public Fv3VertexArray {

    float xp;

 public:
    const Font& font;

    float minX;
    float midX;
    float maxX;
    float minY;
    float midY;
    float maxY;
    float minZ;
    float midZ;
    float maxZ;

    unsigned int count;  // number of 3-vertices

    /*
     */
    FontGlyphVector(const Font&);
    /*!
     * Append characters left to right (X+).
     */
    FontGlyphVector(const Font&,const char*);
    /*
     * Subtype of vertex array
     */
    virtual ~FontGlyphVector();

    /*!
     * Append characters left to right (X+).
     */
    void append_ltr(const char*);
};

#endif
