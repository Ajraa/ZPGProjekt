#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 cameraFront;
uniform vec3 matAmbient;
uniform vec3 matDiffuse;
uniform float matShininess;
uniform vec3 matSpecular;

void main () {
    vec3 lightDir = lightPosition - ex_worldPosition.xyz / ex_worldPosition.w;
    vec3 viewDir = cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w;
    vec3 reflectDir = reflect(-normalize(lightDir), normalize(ex_worldNormal));
    float dot_product = max(dot(normalize(lightDir), normalize(ex_worldNormal)), 0.0);
    float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), (matShininess * 128));
    
    vec4 specular = vec4(matSpecular, 1.0) * spec * lightColor;
    if (dot(ex_worldNormal , lightDir) <= 0.0) { 
        specular = vec4(0.0 , 0.0 , 0.0 , 0.0); 
    }
    
    float theta = dot(normalize(lightDir), normalize(-cameraFront));
    
    vec4 ambient = lightColor * vec4(matAmbient, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

    if (theta > cos(radians(30.0))) {
        vec4 diffuse = dot_product * vec4(matDiffuse, 1.0) * lightColor;
        float dist = distance(lightPosition, ( ex_worldPosition.xyz / ex_worldPosition.w));
        float att = 1.0 / (1.0 + 0.01*dist + 0.01*dist*dist);
        out_Color = (ambient + diffuse + specular) * objectColor * att;
    } else {
         out_Color = vec4(0.0 , 0.0 , 0.0 , 0.0);
    }
    
}