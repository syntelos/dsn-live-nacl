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
#ifndef _DSNL_Fv3Vector_H
#define _DSNL_Fv3Vector_H

#include "Fv3.h"

/*!
 * 
 */
class Fv3Vector : public Fv3 {

 public:

    float array[3];

    Fv3Vector();
    Fv3Vector(const Fv3Vector&);
    Fv3Vector(const float*);
    ~Fv3Vector();

    virtual unsigned int data_length() const;

    virtual float* data();

    virtual void copy(const float*);


};
#endif
