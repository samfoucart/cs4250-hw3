// Varying means to interpolate the variable across the object
varying vec4 fColor;

void main()
{
  gl_FragColor = (.5 * fColor) + vec4(1.0, 0, 1.0, .5);
}
