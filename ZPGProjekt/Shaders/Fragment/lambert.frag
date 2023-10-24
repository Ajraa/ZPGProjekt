# version 400
in VS_out
{
    vec3 fragNormal;
    vec3 fragPos;
} fs_in;
out vec4 fragColor;
void main()
{
    vec3 lightPosition = vec3(0.0,0.0,0.0);
    vec3 norm = normalize(fs_in.fragNormal);
    vec3 lightDir = normalize(lightPosition - fs_in.fragPos);
    float dot_product = max(dot(lightDir, norm), 0.0);
    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    fragColor = ambient + diffuse;
}