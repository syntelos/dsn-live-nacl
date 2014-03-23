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
 * This class provides some common utility functions, however its
 * public fields, minimality, and lack of universality make this a bit
 * more of a "C struct" than a "C++ class" in some aspects.  The GL
 * fields have no "operators" in this class.  The bounds method is an
 * O(N) tool of last resort.  The append Fv3VertexArray method will
 * maintain bounds, while other append methods do not.  Therefore,
 * subclasses and users must elect an approach to the collection of
 * boundary values as required.  The FontGlyphVector subclass, for
 * example, employs the pre computed bounds found within the font
 * glyph.
 */
class Fv3VertexArray : public Fv3 {

 public:
    /*
     * Vertices
     */
    unsigned int array_length;
    float* array;
    /*
     * Bounds values are initialized to FP_MIN (max) and FP_MAX (min).
     */
    float minX;
    float midX;
    float maxX;
    float minY;
    float midY;
    float maxY;
    float minZ;
    float midZ;
    float maxZ;
    /*
     * GL primitives' type
     */
    GLushort type;
    /*
     * GL buffer index
     */
    GLuint vertex_buffer;
    /*
     * GL primitives' count
     */
    GLsizei elements;

    /*!
     * Create an empty vertex array with array length zero and array
     * pointer null.
     */
    Fv3VertexArray();
    Fv3VertexArray(GLushort);
    /*!
     * Create a non empty vertex array.
     */
    Fv3VertexArray(unsigned int);
    Fv3VertexArray(GLushort,unsigned int);
    Fv3VertexArray(unsigned int,float*);
    Fv3VertexArray(GLushort,unsigned int,float*);
    /*!
     * Copy all fields except the vertex buffer index.
     */
    Fv3VertexArray(const Fv3VertexArray&);
    /*
     */
    virtual ~Fv3VertexArray();

    /*!
     * Returns array length: number of float elements in array.
     */
    virtual unsigned int data_length() const;
    /*!
     * Returns array reference, not a copy.
     */
    virtual float* data();
    /*!
     * The length of the argument is expected to be identical to this
     * array length.
     */
    virtual void copy(const float*);

    void append(const Fv3VertexArray&);

    void append(const unsigned int, const float*);
    /*!
     * Bounds values are not default.
     */
    bool hasBounds() const;
    /*!
     * Bounds values are default.
     */
    bool hasNotBounds() const;
    /*!
     * Scan array as a list of vertices in three coordinates (x, y, z)
     * to update bounds.
     */
    void bounds();

};
#endif
