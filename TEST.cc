/*
 * DSN Live NaCl TEST
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

#include <cstdio>
#include <iostream>

#include "glh.h"
#include "Fv3Color.h"
#include "Fv3Matrix.h"
#include "FontFutural.h"
#include "Shaders.h"

int main(int argc, char** argv){
    const float width = 1600.0;
    const float height = 900.0;

    Fv3Matrix camera(Fv3Matrix::ID);

    const float aspect = (width/height);

    glhPerspectivef2(camera,45.0,aspect,0.0,10.0);

    FontFutural font;

    FontGlyphVector *string = new FontGlyphVector(font,"string");

    std::printf("string len_fv3: %d, minX: %f, midX: %f, maxX: %f\n",string->array_length,string->minX, string->midX, string->maxX);


    return 0;

}
