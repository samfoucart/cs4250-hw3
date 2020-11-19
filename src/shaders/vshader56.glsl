// Shader for computation of colors at each fragment
// 
// Original code from Angel
//
// Modified by David Chelberg
// last-modified: Sun Nov 15 13:58:06 2020
// 
attribute   vec4 vPosition;
attribute   vec4 vNormal;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;

uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform mat4 Projection;

void main()
{
  fN = vNormal.xyz;
  fE = vPosition.xyz;
  fL = LightPosition.xyz;
    
  //  if(LightPosition.w != 0.0) {
  //    fL = LightPosition.xyz - vPosition.xyz;
  //  }

  gl_Position = Projection*ModelView*vPosition;
}
