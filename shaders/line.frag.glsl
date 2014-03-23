#version 100
precision mediump float;

uniform mat4 u_camera;
uniform vec4 u_color;

void main(){

    gl_FragColor = u_color;
}
