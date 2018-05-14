#version 330

layout (location = 0) in vec3 in_position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 v_position;

void main(void)
{
	v_position = in_position;
	gl_Position = projection * view * model * vec4(in_position, 1.0);
}