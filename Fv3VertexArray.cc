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
#include <cstdlib>

#include "Fv3VertexArray.h"

Fv3VertexArray::Fv3VertexArray()
    : array_length(0), 
      array(0),
      minX(FP_MAX), midX(ZERO), maxX(FP_MIN),
      minY(FP_MAX), midY(ZERO), maxY(FP_MIN),
      minZ(FP_MAX), midZ(ZERO), maxZ(FP_MIN),
      type(0),
      vertex_buffer(0),
      elements(0)
{
}
Fv3VertexArray::Fv3VertexArray(GLushort type)
    : array_length(0), 
      array(0),
      minX(FP_MAX), midX(ZERO), maxX(FP_MIN),
      minY(FP_MAX), midY(ZERO), maxY(FP_MIN),
      minZ(FP_MAX), midZ(ZERO), maxZ(FP_MIN),
      type(type),
      vertex_buffer(0),
      elements(0)
{
}
Fv3VertexArray::Fv3VertexArray(unsigned int count)
    : array_length(count), 
      array((float*)std::calloc(count,sizeof(float))),
      minX(FP_MAX), midX(ZERO), maxX(FP_MIN),
      minY(FP_MAX), midY(ZERO), maxY(FP_MIN),
      minZ(FP_MAX), midZ(ZERO), maxZ(FP_MIN),
      type(0),
      vertex_buffer(0),
      elements(0)
{
}
Fv3VertexArray::Fv3VertexArray(GLushort type, unsigned int count)
    : array_length(count), 
      array((float*)std::calloc(count,sizeof(float))),
      minX(FP_MAX), midX(ZERO), maxX(FP_MIN),
      minY(FP_MAX), midY(ZERO), maxY(FP_MIN),
      minZ(FP_MAX), midZ(ZERO), maxZ(FP_MIN),
      type(type),
      vertex_buffer(0),
      elements(0)
{
}
Fv3VertexArray::Fv3VertexArray(unsigned int count, float* copy)
    : array_length(count), array(0), 
      minX(FP_MAX), midX(ZERO), maxX(FP_MIN),
      minY(FP_MAX), midY(ZERO), maxY(FP_MIN),
      minZ(FP_MAX), midZ(ZERO), maxZ(FP_MIN),
      type(0),
      vertex_buffer(0),
      elements(0)
{
    this->copy(copy);
}
Fv3VertexArray::Fv3VertexArray(GLushort type, unsigned int count, float* copy)
    : array_length(count), array(0), 
      minX(FP_MAX), midX(ZERO), maxX(FP_MIN),
      minY(FP_MAX), midY(ZERO), maxY(FP_MIN),
      minZ(FP_MAX), midZ(ZERO), maxZ(FP_MIN),
      type(type),
      vertex_buffer(0),
      elements(0)
{
    this->copy(copy);
}
Fv3VertexArray::Fv3VertexArray(const Fv3VertexArray& copy)
    : array_length(copy.array_length), array(0),
      minX(copy.minX), midX(copy.midX), maxX(copy.maxX),
      minY(copy.minY), midY(copy.midY), maxY(copy.maxY),
      minZ(copy.minZ), midZ(copy.midZ), maxZ(copy.maxZ),
      type(copy.type),
      vertex_buffer(0),
      elements(copy.elements)
{
    this->copy(copy.array);
}
Fv3VertexArray::~Fv3VertexArray()
{
    if (0 != array){
        delete array;
    }
}
unsigned int Fv3VertexArray::data_length() const {
    return array_length;
}
float* Fv3VertexArray::data(){
    return array;
}
void Fv3VertexArray::copy(const float* copy){
    if (0 != array_length){

        const std::size_t msz = array_length*sizeof(float);

        if (0 == array){
            array = (float*)std::malloc(msz);
        }
        std::memcpy(array,copy,msz);
    }
}
Fv3VertexArray& Fv3VertexArray::append(const Fv3VertexArray& src){

    append(src.array_length,src.array);

    if (src.hasBounds()){

        minX = fmin(minX,src.minX);
        minY = fmin(minY,src.minY);
        minZ = fmin(minZ,src.minZ);

        maxX = fmax(maxX,src.maxX);
        maxY = fmax(maxY,src.maxY);
        maxZ = fmax(maxZ,src.maxZ);

        midX = (minX+maxX)/2.0;
        midY = (minY+maxY)/2.0;
        midZ = (minZ+maxZ)/2.0;
    }
    return *this;
}
Fv3VertexArray& Fv3VertexArray::append(const unsigned int src_array_length, const float* src_array){

    const unsigned int olen = array_length;
    const unsigned int nlen = (olen + src_array_length);

    array = (float*)std::realloc(array,(nlen*sizeof(float)));
    if (array){
        array_length = nlen;

        if (0 < olen){

            float* fp = &(array[olen]);

            std::memcpy(fp,src_array,src_array_length*sizeof(float));
        }
        else {
            std::memcpy(array,src_array,src_array_length*sizeof(float));
        }
    }
    else {
        array_length = 0;
    }
    return *this;
}
bool Fv3VertexArray::hasBounds() const {
    return (FP_MAX != minX && ZERO != midX && FP_MIN != maxX);
}
bool Fv3VertexArray::hasNotBounds() const {
    return (FP_MAX == minX && ZERO == midX && FP_MIN == maxX);
}
Fv3VertexArray& Fv3VertexArray::bounds(){
    if (0 != array && 0 < array_length){
        minX = FP_MAX;
        minY = FP_MAX;
        minZ = FP_MAX;

        maxX = FP_MIN;
        maxY = FP_MIN;
        maxZ = FP_MIN;

        unsigned int cc;
        for (cc = 0; cc < array_length; ){
            float x = array[cc++];
            float y = array[cc++];
            float z = array[cc++];

            minX = fmin(minX,x);
            minY = fmin(minY,y);
            minZ = fmin(minZ,z);

            maxX = fmax(maxX,x);
            maxY = fmax(maxY,y);
            maxZ = fmax(maxZ,z);
        }
        midX = (minX+maxX)/2.0;
        midY = (minY+maxY)/2.0;
        midZ = (minZ+maxZ)/2.0;
    }
    return *this;
}
Fv3VertexArray& Fv3VertexArray::fitTo(float x, float y, float z){

    if (hasBounds()){

        float xx = (maxX-minX);
        float yy = (maxY-minY);
        float zz = (maxZ-minZ);

        float sx = 1.0, sy = 1.0, sz = 1.0;

        if (IS_NOT_ZERO(xx)){
            sx = (x/xx);
        }

        if (IS_NOT_ZERO(yy)){
            sy = (y/yy);
        }

        if (IS_NOT_ZERO(zz)){
            sz = (z/zz);
        }

        float s = fmin(sx,fmin(sy,sz));

        scale(s);
    }
    return *this;
}
Fv3VertexArray& Fv3VertexArray::scale(float s){

    s = static_cast<float>(s);

    if (s == s && IS_NOT_ZERO(s)){

        minX = FP_MAX;
        minY = FP_MAX;
        minZ = FP_MAX;

        maxX = FP_MIN;
        maxY = FP_MIN;
        maxZ = FP_MIN;

        unsigned int cc, ix, iy, iz;

        for (cc = 0; cc < array_length; cc += 3){

            ix = (cc+X);
            iy = (cc+Y);
            iz = (cc+Z);

            float x = (array[ix] * s);
            float y = (array[iy] * s);
            float z = (array[iz] * s);

            array[ix] = x;
            array[iy] = y;
            array[iz] = z;

            minX = fmin(minX,x);
            minY = fmin(minY,y);
            minZ = fmin(minZ,z);

            maxX = fmax(maxX,x);
            maxY = fmax(maxY,y);
            maxZ = fmax(maxZ,z);
        }
        midX = (minX+maxX)/2.0;
        midY = (minY+maxY)/2.0;
        midZ = (minZ+maxZ)/2.0;
    }
    return *this;
}
Fv3VertexArray& Fv3VertexArray::translate(float dx, float dy, float dz){

    minX = FP_MAX;
    minY = FP_MAX;
    minZ = FP_MAX;

    maxX = FP_MIN;
    maxY = FP_MIN;
    maxZ = FP_MIN;

    unsigned int cc, ix, iy, iz;

    for (cc = 0; cc < array_length; cc += 3){

        ix = (cc+X);
        iy = (cc+Y);
        iz = (cc+Z);

        float x = (array[ix] + dx);
        float y = (array[iy] + dy);
        float z = (array[iz] + dz);

        array[ix] = x;
        array[iy] = y;
        array[iz] = z;

        minX = fmin(minX,x);
        minY = fmin(minY,y);
        minZ = fmin(minZ,z);

        maxX = fmax(maxX,x);
        maxY = fmax(maxY,y);
        maxZ = fmax(maxZ,z);
    }
    midX = (minX+maxX)/2.0;
    midY = (minY+maxY)/2.0;
    midZ = (minZ+maxZ)/2.0;

    return *this;
}
Fv3VertexArray& Fv3VertexArray::center(){
    if (hasBounds()){
        if (IS_NOT_ZERO(midX)){

            if (IS_NOT_ZERO(midY)){

                if (IS_NOT_ZERO(midZ)){

                    translate( -midX, -midY, -midZ);
                }
                else {

                    translate( -midX, -midY, 0.0);
                }
            }
            else if (IS_NOT_ZERO(midZ)){

                translate( -midX, 0.0, -midZ);
            }
            else {

                translate( -midX, 0.0, 0.0);
            }
        }
        else if (IS_NOT_ZERO(midY)){

            if (IS_NOT_ZERO(midZ)){

                translate( 0.0, -midY, -midZ);
            }
            else {

                translate( 0.0, -midY, 0.0);
            }
        }
        else if (IS_NOT_ZERO(midZ)){

            translate( 0.0, 0.0, -midZ);
        }
    }
    return *this;
}
