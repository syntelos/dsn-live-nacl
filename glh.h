/*
 * OpenGL Helper Library
 * http://www.opengl.org/wiki/GluPerspective_code
 * Copyright (C) 2001-2011 Vrej Melkonian All Rights Reserved.
 * Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Copyright (c) 2014 John Pritchard, Syntelos.
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
#ifndef __GLES_GLH_H
#define __GLES_GLH_H

#define _USE_MATH_DEFINES 1
#include <limits.h>
#include <math.h>
#include <GLES2/gl2.h>

#include "Fv3Matrix.h"


void glhFrustumf2(Fv3Matrix& m,
                  GLfloat left,
                  GLfloat right,
                  GLfloat bottom,
                  GLfloat top,
                  GLfloat znear,
                  GLfloat zfar);

void glhPerspectivef2(Fv3Matrix& m,
                      GLfloat fovyInDegrees,
                      GLfloat aspectRatio,
                      GLfloat znear,
                      GLfloat zfar);

#endif
