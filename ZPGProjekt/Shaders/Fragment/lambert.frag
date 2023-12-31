#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 matAmbient;
uniform vec3 matDiffuse;
uniform float matShininess;
uniform vec3 matSpecular;

void main () {
    vec3 lightDir = lightPosition - ex_worldPosition.xyz / ex_worldPosition.w;
    float dot_product = max(dot(normalize(lightDir), normalize(ex_worldNormal)), 0.0); 
    vec4 diffuse = dot_product * vec4(matDiffuse, 1.0) * lightColor;
    vec4 ambient = lightColor * vec4(matAmbient, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    out_Color = (ambient + diffuse) * objectColor;
}