#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in mat4 vProjection[];
in mat4 vView[];
in vec2 vTexture[];
in vec4 vColor[];

out vec2 gTexture;
out vec4 gColor;

void main()
{
	float s = 1.0 / 8.0;
	mat4 PV = vProjection[0] * vView[0];
	gColor = vColor[0];

	gTexture = (vec2(0, 0) + vTexture[0]) * vec2(1, -1);
	gl_Position = PV * (gl_in[0].gl_Position + vec4(0.0, -0.5, -0.5, 1.0));
    EmitVertex();

	gTexture = (vec2(s, 0) + vTexture[0]) * vec2(1, -1);
	gl_Position = PV * (gl_in[0].gl_Position + vec4(0.0, 0.5, -0.5, 1.0));
    EmitVertex();

	gTexture = (vec2(s, s) + vTexture[0]) * vec2(1, -1);
	gl_Position = PV * (gl_in[0].gl_Position + vec4(0.0, 0.5, 0.5, 1.0));
    EmitVertex();

	gTexture = (vec2(0, s) + vTexture[0]) * vec2(1, -1);
	gl_Position = PV * (gl_in[0].gl_Position + vec4(0.0, -0.5, 0.5, 1.0));
    EmitVertex();

    EndPrimitive();
}