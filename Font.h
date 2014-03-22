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

#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"


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
/*
 * glyph = vector[ch-'!']
 * 
 * space = em
 */
class Font {
 public:
    const float em;
    const float ascent;
    const float descent;
    const float leading;
    const GLushort mode;

    Font(float em, float ascent, float descent, float leading, GLushort mode);

    virtual const FontGlyph* get(char) const = 0;
};
/*
 */
class FontGlyphVector {
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
    unsigned int length;  // length of vertices array (number of floats)
    unsigned int count;  // number of 3-vertices (length/3)
    float* vertices;
    GLuint vertex_buffer;

    FontGlyphVector(const Font&,const char*);
    ~FontGlyphVector();
};

#endif
