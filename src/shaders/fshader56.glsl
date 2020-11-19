// Fragment shader
// Computes colors per fragment
//
// Based on code from Angel
// 
//
// Modified by David Chelberg
// last-modified: Sun Nov 15 14:01:23 2020
//
// 
varying  vec3 fN;
varying  vec3 fL;
varying  vec3 fE;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform float Shininess;

// For light sources.
uniform vec4 EmmissiveColor;
uniform bool EmmissiveP;

// Bool expressed as an int to pass to shader
//uniform bool Spec;

void main() 
{ 
  if (EmmissiveP) {
    gl_FragColor = EmmissiveColor;
  } else {
    // Normalize the input lighting vectors
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);

    //If nearby light, calculate the direction per fragment.
    if(LightPosition.w != 0.0) {
      L = normalize(fL - fE);
    }

    // Use the half angle approximation
    //    vec3 H = normalize(L + E);

    // Compute the exact reflectance angle
    vec3 R = reflect(L, N);
    R = normalize(R);

    vec4 ambient = AmbientProduct;

    // Front side lighting only
    float Kd = max(dot(L, N), 0.0);

    // Doubles sided lighting below
    //    float Kd = abs(dot(L, N));
    vec4 diffuse = Kd*DiffuseProduct;
    
    // Use the actual reflected vector
    // If we want to use the half-angle approximation, we need to
    // modify this.
    float Ks = pow(max(dot(R, -E), 0.0), Shininess);
    vec4 specular = Ks*SpecularProduct;

    // discard the specular highlight if the light's behind the vertex
    if(dot(R, -E) < 0.0) {
      specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    /*
    // If we use half way vector:
    float Ks = pow(max(dot(N, H), 0.0), Shininess);
    vec4 specular = Ks*SpecularProduct;

    // discard the specular highlight if the light's behind the vertex
    if(dot(L, N) < 0.0) {
      specular = vec4(0.0, 0.0, 0.0, 1.0);
    }
    */

    //    if (!Spec) {
    //      specular = vec4(0.0, 0.0, 0.0, 1.0);
    //    }

    // Next lines are for a nearby light source with inverse square
    // drop-off with distance. (Note, coefficients should be passed in
    // uniforms for complete generality).

    //    gl_FragColor =
    //    (1.0/(0.25+0.25*pow(length(fL),2.0)+0.25*length(fL)))*(ambient
    //    + diffuse + specular);
    gl_FragColor = (ambient + diffuse + specular);
    gl_FragColor.a = 1.0;
  }
} 

