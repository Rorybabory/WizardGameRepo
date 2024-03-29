#version 120
attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
varying vec3 normal0;
varying vec2 texCoord0;
varying int x0;
varying int y0;
uniform mat4 transform;
uniform int x;
uniform int y;
void main() {
  x0 = x;
  y0 = y;
  gl_Position = transform * vec4(position, 1.0);
  texCoord0 = texCoord*vec2(1.0,-1.0);
  normal0 = (transform * vec4(normal, 0.0)).xyz;
}
