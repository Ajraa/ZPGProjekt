#version 330

layout(location = 0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 texCoords;

void main () {
	mat4 viewNoTranslation = mat4(mat3(viewMatrix));
	vec4 pos = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    gl_Position = pos;
	texCoords = vp;
}