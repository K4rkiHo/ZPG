#version 330
layout(location=0) in vec3 ex_Position;
layout(location=1) in vec3 in_Normal;
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main () {
	ex_worldPosition = modelMatrix * vec4(ex_Position, 1.0);
	ex_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * in_Normal);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(ex_Position, 1.0);
};