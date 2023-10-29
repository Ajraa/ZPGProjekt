# version 400
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec4 fragColor;
uniform vec3 lightPosition;
uniform vec4 lightColor;
void main()
{
    vec3 norm = normalize(fs_in.fragNormal);
    vec3 lightDir = lightPosition - ex_worldPosition.xyz / ex_worldPosition.w;
    float dot_product = max(dot(lightDir, norm), 0.0);
    vec4 diffuse = dot_product * lightColor;
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    fragColor = ambient + diffuse;
}