/*
 * OpenGL Helper Library
 * http://www.opengl.org/wiki/GluPerspective_code
 * Copyright (C) 2001-2011 Vrej Melkonian All Rights Reserved.
 * Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Copyright (c) 2014 John Pritchard, Syntelos
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
#include <stdlib.h>
#include <string.h>

#include "glh.h"

void glhFrustumf2(Fv3Matrix& m,
                  GLfloat left,
                  GLfloat right,
                  GLfloat bottom,
                  GLfloat top,
                  GLfloat znear,
                  GLfloat zfar)
{
    float *mat = m.array;
    float temp, temp2, temp3, temp4;
    temp = 2.0f * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    mat[0] = temp / temp2;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;
    mat[4] = 0.0f;
    mat[5] = temp / temp3;
    mat[6] = 0.0f;
    mat[7] = 0.0f;
    mat[8] = (right + left) / temp2;
    mat[9] = (top + bottom) / temp3;
    mat[10] = (-zfar - znear) / temp4;
    mat[11] = -1.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = (-temp * zfar) / temp4;
    mat[15] = 0.0f;
}

void glhPerspectivef2(Fv3Matrix& m,
                      GLfloat fovyInDegrees,
                      GLfloat aspectRatio,
                      GLfloat znear,
                      GLfloat zfar)
{
    float ymax, xmax;
    ymax = znear * tanf(fovyInDegrees * 3.14f / 360.0f);
    xmax = ymax * aspectRatio;
    glhFrustumf2(m, -xmax, xmax, -ymax, ymax, znear, zfar);
}
