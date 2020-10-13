attribute vec2 vPosition;
attribute vec2 vColor;
uniform float zoomPercentage;
uniform vec2 translation;
varying vec4 fColor;
uniform vec2 windowSize;

void main()
{
  float aspectRatio = windowSize.x / windowSize.y;
  gl_Position.x = zoomPercentage * ((vPosition.x / aspectRatio) - translation.x);
  gl_Position.y = zoomPercentage * ((vPosition.y * aspectRatio) + translation.y);
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;

  fColor.x = vColor.x;
  fColor.y = 0.0;
  fColor.z = vColor.y;
  fColor.w = 1.0;
}
