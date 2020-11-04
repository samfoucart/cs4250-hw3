attribute vec4 vPosition;
uniform vec4 vColor;
uniform mat4 viewRotation;
varying vec4 fColor;

void main()
{
  gl_Position = viewRotation * vPosition;

  fColor = vColor;
}