# version 400
in VS_out
{
    vec3 fragNormal;
    vec3 fragPos;
} fs_in;
out vec4 fragColor;
void main ()
{
    vec3 lightPosition = vec3(0.0,0.0,0.0);
    vec3 norm = normalize(fs_in.fragNormal);
    vec3 pos = fs_in.fragPos;
    vec3 lightDir = normalize(lightPosition - pos);
    vec3 halfwayDir = normalize ( lightDir + norm );

    float spec = pow( max( dot( norm , halfwayDir ), 0.0) ,32);

    vec4 diffuse = spec * vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
    float specularStrength = 0.1;
    vec4 specular = specularStrength * spec * lightColor;
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    fragColor =( ambient + diffuse + specular )* objectColor;
}