attribute vec2 vPosition;
attribute vec2 vColor;
uniform float zoomPercentage;
uniform vec2 translation;
varying vec4 fColor;

void main()
{
  gl_Position.x = zoomPercentage * (vPosition.x - translation.x);
  gl_Position.y = zoomPercentage * (vPosition.y + translation.y);
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;

  fColor.x = vColor.x;
  fColor.y = 0.0;
  fColor.z = vColor.y;
  fColor.w = 1.0;
}
