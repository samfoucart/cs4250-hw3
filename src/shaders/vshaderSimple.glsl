attribute vec2 vPosition;
attribute vec2 vColor;
uniform float zoomPercentage;
varying vec4 fColor;

void main()
{
  gl_Position.x = zoomPercentage * vPosition.x;
  gl_Position.y = zoomPercentage * vPosition.y;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;

  fColor.x = vColor.x;
  fColor.y = 0.0;
  fColor.z = vColor.y;
  fColor.w = 1.0;
}
