#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec4 inColor;

out vec4 outColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    //gl_Position = modelMatrix * vec4(vp,1.0);
    outColor = inColor;
}