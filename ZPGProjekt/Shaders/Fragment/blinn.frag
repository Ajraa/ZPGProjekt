#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
void main () {
    vec3 lightDir = normalize(lightPosition - ex_worldPosition.xyz / ex_worldPosition.w);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    float dot_product = max(dot(lightDir, ex_worldNormal), 0.0);
    float spec = pow(max(dot(halfwayDir, ex_worldNormal), 0.0), 16.0);
    vec4 specular = spec * lightColor;
    if (dot(ex_worldNormal , lightDir) <= 0.0) { 
        specular = vec4 (0.0 , 0.0 , 0.0 , 0.0); 
    }
    
    vec4 diffuse = dot_product * lightColor;
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    out_Color = (ambient + diffuse + specular) * objectColor;
}



