#version 330
layout(location=0) in vec3 ex_worldPosition;
layout(location=1) in vec3 in_Normal;
out vec3 out_colour;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main () {
     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(ex_worldPosition, 1.0);
	 out_colour = vec3(0.0, 1.0, 0.0);
};