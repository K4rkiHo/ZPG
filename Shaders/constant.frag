#version 330
in vec3 out_colour;
out vec4 frag_colour;
uniform float ambientStrength;
void main () {
     vec3 ambient = ambientStrength * out_colour; 
     frag_colour = vec4(ambient, 1.0);
};