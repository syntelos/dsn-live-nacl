#version 100
precision mediump float;

uniform mat4 u_camera;
uniform vec4 u_color;

attribute vec4 a_position;
attribute vec4 a_normal;

void main(){

  gl_Position = u_camera * a_position;
}
