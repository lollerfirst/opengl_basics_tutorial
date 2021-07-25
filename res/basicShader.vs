#version 120

attribute vec3 position;
attribute vec2 tex_coord;

varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = tex_coord;
}
