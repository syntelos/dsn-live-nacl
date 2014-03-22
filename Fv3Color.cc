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

#include "Fv3Color.h"

const Fv3Color Fv3Color::White = Fv3Color( 1.0f, 1.0f, 1.0f, 1.0f);
const Fv3Color Fv3Color::LightGray = Fv3Color( 0.75294117647058823529f, 0.75294117647058823529f, 0.75294117647058823529f, 1.0f);
const Fv3Color Fv3Color::Gray = Fv3Color( 0.50196078431372549019f, 0.50196078431372549019f, 0.50196078431372549019f, 1.0f);
const Fv3Color Fv3Color::DarkGray = Fv3Color( 0.25098039215686274509f, 0.25098039215686274509f, 0.25098039215686274509f, 1.0f);
const Fv3Color Fv3Color::Black = Fv3Color( 0.0f, 0.0f, 0.0f, 1.0f);
const Fv3Color Fv3Color::Red = Fv3Color( 1.0f, 0.0f, 0.0f, 1.0f);
const Fv3Color Fv3Color::Pink = Fv3Color( 1.0f, 0.68627450980392156862f, 0.68627450980392156862f, 1.0f);
const Fv3Color Fv3Color::Orange = Fv3Color( 1.0f, 0.78431372549019607843f, 0.0f, 1.0f);
const Fv3Color Fv3Color::Yellow = Fv3Color( 1.0f, 1.0f, 0.0f, 1.0f);
const Fv3Color Fv3Color::Green = Fv3Color( 0.0f, 1.0f, 0.0f, 1.0f);
const Fv3Color Fv3Color::Magenta = Fv3Color( 1.0f, 0.0f, 1.0f, 1.0f);
const Fv3Color Fv3Color::Cyan = Fv3Color( 0.0f, 1.0f, 1.0f, 1.0f);
const Fv3Color Fv3Color::Blue = Fv3Color( 0.0f, 0.0f, 1.0f, 1.0f);

Fv3Color::Fv3Color()
{
}
Fv3Color::Fv3Color(const Fv3Color& copy)
{
    this->copy(copy.array);
}
Fv3Color::Fv3Color(const float* copy)
{
    this->copy(copy);
}
Fv3Color::Fv3Color(float r, float g, float b, float a){
    array[R] = r;
    array[G] = g;
    array[B] = b;
    array[A] = a;
}
Fv3Color::~Fv3Color()
{
}
unsigned int Fv3Color::data_length() const {
    return 4;
}
float* Fv3Color::data(){
    return array;
}
void Fv3Color::copy(const float* copy){
    std::memcpy(array,copy,3*sizeof(float));
}

