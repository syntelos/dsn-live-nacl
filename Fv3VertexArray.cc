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
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      type(0),
      vertex_buffer(0)
{
}
Fv3VertexArray::Fv3VertexArray(GLushort type)
    : array_length(0), 
      array(0),
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      type(type),
      vertex_buffer(0)
{
}
Fv3VertexArray::Fv3VertexArray(unsigned int count)
    : array_length(count), 
      array((float*)std::malloc(count*sizeof(float))),
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      type(0),
      vertex_buffer(0)
{
}
Fv3VertexArray::Fv3VertexArray(GLushort type, unsigned int count)
    : array_length(count), 
      array((float*)std::malloc(count*sizeof(float))),
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      type(type),
      vertex_buffer(0)
{
}
Fv3VertexArray::Fv3VertexArray(unsigned int count, float* copy)
    : array_length(count), array(0), 
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      type(0),
      vertex_buffer(0)
{
    this->copy(copy);
}
Fv3VertexArray::Fv3VertexArray(GLushort type, unsigned int count, float* copy)
    : array_length(count), array(0), 
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      type(type),
      vertex_buffer(0)
{
    this->copy(copy);
}
Fv3VertexArray::Fv3VertexArray(const Fv3VertexArray& copy)
    : array_length(copy.array_length), array(0),
      minX(0), midX(0), maxX(0),
      minY(0), midY(0), maxY(0),
      minZ(0), midZ(0), maxZ(0),
      type(copy.type),
      vertex_buffer(0)
{
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

        if (0 == array){
            array = (float*)std::malloc(array_length*sizeof(float));
        }
        std::memcpy(array,copy,array_length*sizeof(float));
    }
}
void Fv3VertexArray::append(const Fv3VertexArray& src){

    append(src.array_length,src.array);
}
void Fv3VertexArray::append(const unsigned int src_array_length, const float* src_array){

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
}
void Fv3VertexArray::bounds(){
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
}
