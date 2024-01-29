#version 330
in vec3 out_colour;
out vec4 frag_colour;
void main () {
     frag_colour = vec4 (out_colour, 1.0);
};