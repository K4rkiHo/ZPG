#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform vec3 camera_pos;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 objectColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;
uniform float typeLight;
uniform vec3 lightDirection;
uniform vec3 camera_dir;
out vec4 out_Color;

void main() {
    vec3 world_normal = normalize(ex_worldNormal);
    vec3 lightVector = normalize(lightPosition.xyz - ex_worldPosition.xyz);

    float dot_product = max(dot(world_normal, lightVector), 0.0);
    vec4 diffuse = dot_product * lightColor;
    vec4 ambient = ambientStrength * lightColor;

    vec3 view_dir = normalize(camera_pos - ex_worldPosition.xyz);
    vec3 reflect_dir = reflect(-lightVector, world_normal);

    vec3 half_vector = normalize(view_dir + lightVector);
    //vec4 color = vec4(0.0, 1.0, 0.0, 0.0);

    float spec = pow(max(dot(world_normal, half_vector), 0.0), shininess);
    vec4 specular = specularStrength * spec * lightColor ; //*color 

    if (dot_product <= 0.0)
    {
        specular = vec4(0, 0, 0, 0);
        out_Color = (ambient + diffuse + specular) * objectColor;
    }
    else
    {
        out_Color = (ambient + diffuse + specular) * objectColor;
    }
}