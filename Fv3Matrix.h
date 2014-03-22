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
#ifndef _DSNL_Fv3Matrix_H
#define _DSNL_Fv3Matrix_H

#include "Fv3.h"

/*!
 * 
 */
class Fv3Matrix : public Fv3 {

    const static float Identity[16];

 public:
    const static Fv3Matrix ID;

    float array[16];

    Fv3Matrix();
    Fv3Matrix(const Fv3Matrix&);
    Fv3Matrix(const float*);
    ~Fv3Matrix();

    virtual unsigned int data_length() const;

    virtual float* data();

    virtual void copy(const float*);

    void identity();
};
#endif
