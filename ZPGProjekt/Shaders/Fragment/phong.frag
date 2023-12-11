#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 vt_out;
out vec4 out_Color;

uniform vec3 cameraPosition;
uniform vec3 cameraFront;
uniform vec3 matAmbient;
uniform vec3 matDiffuse;
uniform float matShininess;
uniform vec3 matSpecular;
uniform sampler2D textureUnitID;

struct LightPoint {
    vec4 lightColor;
    vec3 lightPosition;
    int type;
    vec3 lightDirection;
};

uniform LightPoint lights[3];

void calculatePoint(int i) {
    vec3 lightDir = lights[i].lightPosition - ex_worldPosition.xyz / ex_worldPosition.w;
    vec3 viewDir = cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w;
    vec3 reflectDir = reflect(-normalize(lightDir), normalize(ex_worldNormal));
    float dot_product = max(dot(normalize(lightDir), normalize(ex_worldNormal)), 0.0);
    float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), (matShininess * 128));
    vec4 specular = vec4(matSpecular, 1.0) * spec * lights[i].lightColor;
    if (dot(ex_worldNormal , lightDir) <= 0.0) { 
        specular = vec4(0.0 , 0.0 , 0.0 , 0.0); 
    }
        
    vec4 diffuse = dot_product * vec4(matDiffuse, 1.0) * lights[i].lightColor;
    vec4 ambient = lights[i].lightColor * vec4(matAmbient, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    float dist = distance(lights[i].lightPosition, ( ex_worldPosition.xyz / ex_worldPosition.w));
    float att = 1.0 / (1.0 + 0.01*dist + 0.01*dist*dist);
    out_Color += (ambient + diffuse + specular) * objectColor * att;
}

void calculateDirection(int i) {
    vec3 lightDir = normalize(lights[i].lightDirection);
    vec3 viewDir = cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w;
    vec3 reflectDir = reflect(-lightDir, normalize(ex_worldNormal));
    float dot_product = max(dot(lightDir, normalize(ex_worldNormal)), 0.0);
    float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), (matShininess * 128));
    vec4 specular = vec4(matSpecular, 1.0) * spec * lights[i].lightColor;
    if (dot(ex_worldNormal , lightDir) <= 0.0) { 
        specular = vec4(0.0 , 0.0 , 0.0 , 0.0); 
    }
        
    vec4 diffuse = dot_product * vec4(matDiffuse, 1.0) * lights[i].lightColor;
    vec4 ambient = lights[i].lightColor * vec4(matAmbient, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    float dist = distance(lights[i].lightPosition, ( ex_worldPosition.xyz / ex_worldPosition.w));
    float att = 1.0 / (1.0 + 0.01*dist + 0.01*dist*dist);
    out_Color += (ambient + diffuse + specular) * objectColor;
}

void asfas(int i) {
    vec3 lightDir = lights[i].lightPosition - ex_worldPosition.xyz / ex_worldPosition.w;
    vec3 viewDir = cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w;
    vec3 reflectDir = reflect(-normalize(lightDir), normalize(ex_worldNormal));
    float dot_product = max(dot(normalize(lightDir), normalize(ex_worldNormal)), 0.0);
    float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), (matShininess * 128));
    vec4 specular = vec4(matSpecular, 1.0) * spec * lights[i].lightColor;
    vec4 diffuse = dot_product * vec4(matDiffuse, 1.0) * lights[i].lightColor;
    vec4 ambient = lights[i].lightColor * vec4(matAmbient, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    float dist = distance(lights[i].lightPosition, ( ex_worldPosition.xyz / ex_worldPosition.w));
    float att = 1.0 / (1.0 + 0.01*dist + 0.01*dist*dist);
    if (dot(ex_worldNormal , lightDir) <= 0.0) { 
        specular = vec4(0.0 , 0.0 , 0.0 , 0.0); 
    }

     float theta = dot(normalize(lightDir), normalize(-cameraFront));
    if (theta > cos(radians(30.0))) {
        out_Color += (ambient + diffuse + specular) * objectColor * att;
    } else {
        out_Color += vec4(0.0);
    }
}

void calculateSpotlight(int i) {
       vec3 lightDir = lights[i].lightPosition - ex_worldPosition.xyz / ex_worldPosition.w;
        float distance =  length(lightDir);
        float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));
        vec3 viewDir = cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w;
        vec3 reflectDir = reflect(-normalize(lightDir), normalize(ex_worldNormal));
        float dot_product = max(dot(normalize(lightDir), normalize(ex_worldNormal)), 0.0);
        float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), (matShininess * 128));
        vec4 specular = vec4(matSpecular, 1.0) * spec * lights[i].lightColor;

        if (dot(ex_worldNormal , lightDir) <= 0.0) 
        { 
            specular = vec4 (0.0 , 0.0 , 0.0 , 0.0); 
        }
        
        vec4 diffuse = dot_product * vec4(matDiffuse, 1.0) * lights[i].lightColor;
        vec4 ambient = lights[i].lightColor * vec4(matAmbient, 1.0);
        float theta = dot(normalize(lightDir), normalize(-cameraFront));
        float epsilon = cos(radians(15.0)) - cos(radians(20.0));
        float intensity = clamp((theta - cos(radians(20.0))) / epsilon, 0.0, 1.0);
        diffuse = diffuse * intensity;
        specular = specular * intensity;
        if (theta > cos(radians(30.0))) 
        {
            out_Color += out_Color + (ambient+  diffuse + specular)  * attenuation;
        }
}

void main () {
    vec4 texColor = texture(textureUnitID, vt_out);
    out_Color = vec4(0.0);
    for (int i = 0; i < 3; i++) {

        if (lights[i].type == 0)
            calculatePoint(i);

        if (lights[i].type == 1)
            calculateDirection(i); 

        if (lights[i].type == 2) 
            calculateSpotlight(i);
              
    }
   out_Color *= texColor;
}


