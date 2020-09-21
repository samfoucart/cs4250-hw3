attribute vec2 vPosition;
uniform float zoomPercentage;

void main()
{
  gl_Position.x = zoomPercentage * vPosition.x;
  gl_Position.y = zoomPercentage * vPosition.y;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;
}
