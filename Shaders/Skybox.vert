#version 450
layout(location = 0) in vec3 vp;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentLocalPosition;


void main () {
	
	 mat4 view = mat4(mat3(viewMatrix)); //getout transformations from viewMatrix
	 gl_Position = (projectionMatrix * view ) * vec4(vp, 1.0) * 0.5;
	 
	 fragmentLocalPosition = vp;


}
