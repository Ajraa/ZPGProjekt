# version 400
in VS_out
{
    vec3 fragNormal;
    vec3 fragPos;
} fs_in;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 cameraPosition;
out vec4 fragColor;
void main ()
{
    vec3 norm = normalize(fs_in.fragNormal);
    vec3 viewDir = normalize(cameraPosition - fs_in.fragPos);
    vec3 lightDir = normalize(lightPosition - fs_in.fragPos);
    vec3 reflectDir = reflect(- lightDir , norm );


    float dot_product = max(dot(lightDir, norm), 0.0);
    float spec = pow( max( dot( viewDir , reflectDir ), 0.0), 32);

    float specularStrength = 2;
    vec4 specular;
    if (dot_product <= 0.0) specular = vec4(0.0);
    else specular = specularStrength * spec * lightColor;

    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
   
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    fragColor = (ambient + diffuse + specular) * objectColor;
}