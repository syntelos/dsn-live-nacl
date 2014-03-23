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

const char* LineVert = 
    "#version 100\n"
    "precision mediump float;\n"
    "\n"
    "uniform mat4 u_camera;\n"
    "uniform vec4 u_color;\n"
    "\n"
    "attribute vec4 a_position;\n"
    "attribute vec4 a_normal;\n"
    "\n"
    "void main(){\n"
    "\n"
    "  gl_Position = u_camera * a_position;\n"
    "}\n"
;

const char* LineFrag = 
    "#version 100\n"
    "precision mediump float;\n"
    "\n"
    "uniform mat4 u_camera;\n"
    "uniform vec4 u_color;\n"
    "\n"
    "void main(){\n"
    "\n"
    "    gl_FragColor = u_color;\n"
    "}\n"
;
