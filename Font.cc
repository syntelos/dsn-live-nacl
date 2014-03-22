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

#include "Font.h"

#include <cmath>
#include <cstring>
#include <cstdlib>

Font::Font(float em, float ascent, float descent, float leading, GLushort mode)
    : em(em), ascent(ascent), descent(descent), leading(leading), mode(mode)
{
}
FontGlyphVector::FontGlyphVector(const Font& font, const char* string)
    : font(font),
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      length(0), count(0), vertices(0),
      vertex_buffer(0)
{
    unsigned int string_len = std::strlen(string);
    if (0 < string_len){
        /*
         * build vertex array for string
         */
        float xp = 0;
        unsigned int cc;
        for (cc = 0; cc < string_len; cc++){

            const FontGlyph* glyph = font.get(string[cc]);
            if (0 == glyph){
                /*
                 * translate string geometry for space character
                 */
                xp += font.em;
            }
            else {
                /*
                 * copy glyph into string memory
                 */
                unsigned int nlen = (length+glyph->length);

                vertices = (float*)std::realloc(vertices,(nlen*sizeof(float)));

                if (vertices){

                    float* fp = &(vertices[length]);

                    std::memcpy(fp,glyph->vertices,(glyph->length*sizeof(float)));

                    /*
                     * translate glyph into string geometry
                     */
                    unsigned int xo;
                    for (xo = 0; xo < nlen; ){

                        if (0 != xp){
                            fp[xo] += xp;
                        }
                        float x = fp[xo++];
                        float y = fp[xo++];
                        float z = fp[xo++];

                        minX = fmin(minX,x);
                        minY = fmin(minY,y);
                        minZ = fmin(minZ,z);

                        maxX = fmax(maxX,x);
                        maxY = fmax(maxY,y);
                        maxZ = fmax(maxZ,z);
                    }

                    /*
                     * increment string geometry
                     */
                    xp += glyph->maxX;

                    /*
                     * update glyph vector state
                     */
                    length = nlen;
                    count = (nlen/3);

                    midX = (minX+maxX)/2.0;
                    midY = (minY+maxY)/2.0;
                    midZ = (minZ+maxZ)/2.0;
                }
                else {
                    return;
                }
            }
        }
    }
}
FontGlyphVector::~FontGlyphVector(){

    delete vertices;
}
