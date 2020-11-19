// Basic fragment shader
//
// Based on code from Angel
// outputs interpolated vertex colors
//
// Modified by David Chelberg
// last-modified: Sun Nov 15 14:00:36 2020
//
varying  vec4 color;

void main() 
{ 
    gl_FragColor = color;
} 

