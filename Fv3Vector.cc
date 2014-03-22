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

#include "Fv3Vector.h"

Fv3Vector::Fv3Vector()
{
}
Fv3Vector::Fv3Vector(const Fv3Vector& copy)
{
    this->copy(copy.array);
}
Fv3Vector::Fv3Vector(const float* copy)
{
    this->copy(copy);
}
Fv3Vector::~Fv3Vector()
{
}
unsigned int Fv3Vector::data_length() const {
    return 3;
}
float* Fv3Vector::data(){
    return array;
}
void Fv3Vector::copy(const float* copy){
    std::memcpy(array,copy,3*sizeof(float));
}

