attribute vec4 vPosition;
//uniform mat4 wingRotation;
//uniform mat4 viewRotation;
uniform mat4 scaling;
uniform mat4 translation;
varying vec4 fColor;

void main()
{
 //gl_Position = viewRotation * translation * rotation * scaling * vPosition;
  gl_Position = scaling * translation * vPosition;

  fColor.x = 1.0;
  fColor.y = 0.0;
  fColor.z = 0.0;
  fColor.w = 1.0;
}