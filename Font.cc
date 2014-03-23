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
Font::~Font(){
}
FontGlyphVector::FontGlyphVector(const Font& font)
    : Fv3VertexArray(font.mode),
      xp(0),
      font(font)
{
}
FontGlyphVector::FontGlyphVector(const Font& font, const char* string)
    : Fv3VertexArray(font.mode),
      xp(0),
      font(font)
{
    append_ltr(string);
}
FontGlyphVector::~FontGlyphVector(){
}
void FontGlyphVector::append_ltr(const char*string){
    unsigned int string_len = std::strlen(string);
    if (0 < string_len){
        /*
         * build vertex array for string
         */
        unsigned int cc;
        for (cc = 0; cc < string_len; cc++){

            char ch = string[cc];

            const FontGlyph* glyph = font.get(ch);
            if (0 == glyph){
                /*
                 * translate string geometry for space character
                 */
                float fx = xp+font.em;

                minX = fmin(minX,fx);
                maxX = fmax(maxX,fx);

                xp += font.em;
            }
            else {
                /*
                 * copy glyph into string memory
                 */
                const unsigned int olen = array_length;
                const unsigned int nlen = (olen+glyph->length);
                /*
                 */
                append(glyph->length,glyph->vertices);

                if (array){

                    float* fp = &(array[olen]);
                    /*
                     * translate glyph into string geometry
                     */
                    if (0 != xp){
                        minX = fmin(minX,xp+glyph->minX);
                        minY = fmin(minY,glyph->minY);
                        minZ = fmin(minZ,glyph->minZ);

                        maxX = fmax(maxX,xp+glyph->maxX);
                        maxY = fmax(maxY,glyph->maxY);
                        maxZ = fmax(maxZ,glyph->maxZ);

                        unsigned int xo;
                        for (xo = olen; xo < nlen; xo += 3){

                            fp[xo] += xp;
                        }
                    }
                    else {
                        minX = fmin(minX,glyph->minX);
                        minY = fmin(minY,glyph->minY);
                        minZ = fmin(minZ,glyph->minZ);

                        maxX = fmax(maxX,glyph->maxX);
                        maxY = fmax(maxY,glyph->maxY);
                        maxZ = fmax(maxZ,glyph->maxZ);
                    }
                    /*
                     * increment string geometry
                     */
                    xp += glyph->maxX;
                    /*
                     * update vertex array
                     */
                    elements = (nlen/3);
                }
                else {
                    elements = 0;
                    break;
                }
            }
            midX = (minX+maxX)/2.0;
            midY = (minY+maxY)/2.0;
            midZ = (minZ+maxZ)/2.0;
        }
    }
}
