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

#include <cstring>

#include "Fv3Matrix.h"

const float Fv3Matrix::Identity[16] = {
    1.0f, ZERO, ZERO, ZERO, 
    ZERO, 1.0f, ZERO, ZERO, 
    ZERO, ZERO, 1.0f, ZERO, 
    ZERO, ZERO, ZERO, 1.0f
};
const Fv3Matrix Fv3Matrix::ID = Fv3Matrix();

Fv3Matrix::Fv3Matrix()
{
    this->identity();
}
Fv3Matrix::Fv3Matrix(const Fv3Matrix& copy)
{
    this->copy(copy.array);
}
Fv3Matrix::Fv3Matrix(const float* copy)
{
    this->copy(copy);
}
Fv3Matrix::~Fv3Matrix()
{
}
unsigned int Fv3Matrix::data_length() const {
    return 16;
}
float* Fv3Matrix::data(){
    return array;
}
void Fv3Matrix::copy(const float* copy){
    std::memcpy(array,copy,16*sizeof(float));
}

Fv3Matrix& Fv3Matrix::identity(){
    std::memcpy(array,Identity,16*sizeof(float));
    return *this;
}
Fv3Matrix& Fv3Matrix::ortho(float left, float right,
                            float bottom, float top,
                            float near, float far)
{
    float dx = (right - left);
    float dy = (top - bottom);
    float dz = (far - near);

    float sx = 1.0, sy = 1.0, sz = 1.0;
    float tx = 0.0, ty = 0.0, tz = 0.0;

    if (IS_NOT_ZERO(dx)){

        sx = (2.0 / dx);

        tx = -(right + left) / dx;
    }

    if (IS_NOT_ZERO(dy)){

        sy = (2.0 / dy);

        ty = -(top + bottom) / dy;
    }

    if (IS_NOT_ZERO(dz)){

        sz = (-2.0 / dz);

        tz = -(far + near) / dz;
    }

    array[M00] = sx;
    array[M10] = 0;
    array[M20] = 0;
    array[M30] = 0;
    array[M01] = 0;
    array[M11] = sy;
    array[M21] = 0;
    array[M31] = 0;
    array[M02] = 0;
    array[M12] = 0;
    array[M22] = sz;
    array[M32] = 0;
    array[M03] = tx;
    array[M13] = ty;
    array[M23] = tz;
    array[M33] = 1;

    return *this;
}
