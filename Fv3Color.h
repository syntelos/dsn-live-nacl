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
#ifndef _DSNL_Fv3Color_H
#define _DSNL_Fv3Color_H

#include "Fv3.h"

/*!
 * 
 */
class Fv3Color : public Fv3 {

 public:
    const static Fv3Color White;
    const static Fv3Color LightGray;
    const static Fv3Color Gray;
    const static Fv3Color DarkGray;
    const static Fv3Color Black;
    const static Fv3Color Red;
    const static Fv3Color Pink;
    const static Fv3Color Orange;
    const static Fv3Color Yellow;
    const static Fv3Color Green;
    const static Fv3Color Magenta;
    const static Fv3Color Cyan;
    const static Fv3Color Blue;


    float array[4];

    Fv3Color();
    Fv3Color(const Fv3Color&);
    Fv3Color(const float*);
    Fv3Color(float,float,float,float);
    ~Fv3Color();

    virtual unsigned int data_length() const;

    virtual float* data();

    virtual void copy(const float*);


};
#endif
