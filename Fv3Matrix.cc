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

void Fv3Matrix::identity(){
    std::memcpy(array,Identity,16*sizeof(float));
}
