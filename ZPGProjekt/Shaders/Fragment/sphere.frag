#version 330
out vec4 frag_colour;
in vec3 vertexColor;
void main () {
     frag_colour = vec4(vertexColor, 0.0);
}