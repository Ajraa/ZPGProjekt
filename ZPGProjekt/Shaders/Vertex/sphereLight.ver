#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location = 2) in vec2 vt;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 vt_out;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main () {
    ex_worldPosition = modelMatrix * vec4(vp, 1.0);
    mat4 normalMatrix = transpose(inverse(modelMatrix));
    ex_worldNormal = vec3 ( normalMatrix * vec4 ( vn ,1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp,1.0);
    vt_out = vt;
}