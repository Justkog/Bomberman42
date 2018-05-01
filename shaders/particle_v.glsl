#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexture;
layout(location = 2) in vec3 vertexPositionCenter;
layout(location = 3) in vec2 vertexTextureOffset;
layout(location = 4) in vec4 vertexColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


out vec2 vTexture;
out vec4 vColor;

void main()
{
    vTexture = (vertexTextureOffset + vertexTexture) * vec2(1, -1);
    vColor = vertexColor;

	mat4 VP = projection * view;       
	vec3 CameraRight = vec3(view[0][0], view[1][0], view[2][0]);
	vec3 CameraUp = vec3(view[0][1], view[1][1], view[2][1]);
	float Size = 1.0;
	vec3 vPosition = vec4(vertexPosition, 1.0).xyz;
	gl_Position = VP * vec4(vertexPositionCenter + CameraRight * vPosition.x * Size + CameraUp * vPosition.y * Size, 1.0);
	
	// gl_Position = projection * view * model * vec4(vPosition, 1.0);
}
