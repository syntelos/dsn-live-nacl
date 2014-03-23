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
#ifndef _DSNL_Fv3VertexArray_H
#define _DSNL_Fv3VertexArray_H

#include "Fv3.h"

/*!
 * 
 */
class Fv3VertexArray : public Fv3 {

 public:
    unsigned int array_length;
    float* array;
    float minX;
    float midX;
    float maxX;
    float minY;
    float midY;
    float maxY;
    float minZ;
    float midZ;
    float maxZ;
    GLushort type;
    GLuint vertex_buffer;


    Fv3VertexArray();
    Fv3VertexArray(GLushort);
    Fv3VertexArray(unsigned int);
    Fv3VertexArray(GLushort,unsigned int);
    Fv3VertexArray(unsigned int,float*);
    Fv3VertexArray(GLushort,unsigned int,float*);
    Fv3VertexArray(const Fv3VertexArray&);
    virtual ~Fv3VertexArray();

    virtual unsigned int data_length() const;

    virtual float* data();
    /*!
     * The length of the argument must be identical to the 'count'
     * length in the instance of this class.
     */
    virtual void copy(const float*);

    void append(const Fv3VertexArray&);

    void append(const unsigned int, const float*);
    /*!
     * Scan 3-vectors to update boundary statistics.
     */
    void bounds();

};
#endif
