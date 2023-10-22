# version 400
    in vec4 worldPos;
    in vec3 worldNor;
    out vec4 fragColor;
void main()
{
    vec3 lightPosition = vec3(0.0,0.0,0.0); //správně upravit
    vec3 pos = vec3(worldPos);
    vec3 lightVector = normalize(lightPosition - worldNor);
    float dot_product = max(dot(lightVector, normalize(worldNor)), 0.0);
    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    fragColor = ambient + diffuse;
}
