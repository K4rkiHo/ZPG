#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 objectColor;
uniform float ambientStrength;
uniform float specularStrength;
out vec4 out_Color;
void main() {
    vec3 world_normal = normalize(ex_worldNormal);
    vec3 lightVector = normalize(lightPosition.xyz - ex_worldPosition.xyz);

    float dot_product = max(dot(world_normal, lightVector), 0.0);
    vec4 diffuse = dot_product * lightColor;
    vec4 ambient = ambientStrength * lightColor;

    out_Color = (ambient + diffuse) * objectColor;
}