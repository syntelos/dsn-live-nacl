/*
 * Fv3++
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
#ifndef _DSNL_Fv3Notation_H
#define _DSNL_Fv3Notation_H

#include <cmath>

#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"

/*
 * Common Math constants, epsilon for values 0.0 to 10.0.
 */
#define EPSILON (1e-7f)
#define EPS EPSILON
#define EPS_M2 (EPSILON*2.0f)
#define EPS_D2 (EPSILON/2.0f)
#define EPS_1D2 (1.0f - EPS_D2)

#define PI M_PI
#define PI_D2 (PI / 2.0f)
#define PI_M2 (PI * 2.0f)
#define PI_D3 (PI / 3.0f)
/*
 * Radians per degree.  Multiply by degrees for radians.
 */
#define Degrees (PI / 180.0)
/*
 * Simple zero float
 */
#define ZERO 0.0f
/*
 * Vector array notation
 */
#define X 0
#define Y 1
#define Z 2
/*
 * Matrix array notation
 */
#define M00  0
#define M01  4
#define M02  8
#define M03  12
#define M10  1
#define M11  5
#define M12  9
#define M13  13
#define M20  2
#define M21  6
#define M22  10
#define M23  14
#define M30  3
#define M31  7
#define M32  11
#define M33  15
/*
 * Color array notation
 */
#define R 0
#define G 1
#define B 2
#define A 3

#endif
