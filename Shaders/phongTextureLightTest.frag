#version 450
#define MAX_LIGHTS 8

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
uniform float light_on;

uniform int array_length;

//texture stuff
in vec2 vt_out;
uniform sampler2D textureUnitID;

out vec4 out_Color;

struct Light {
    vec3 camera_pos;
    vec3 lightPosition;
    vec4 lightColor;
    vec4 objectColor;
    float ambientStrength;
    float specularStrength;
    float shininess;
    float typeLight;
    vec3 lightDirection;
    vec3 camera_dir;
    float constant;
    float linear;
    float quadratic;
};

void main() {

    if (typeLight == 1)
    {
        vec3 world_normal = normalize(ex_worldNormal);
        vec3 lightVector = normalize(lightPosition.xyz - ex_worldPosition.xyz);

        float dot_product = max(dot(world_normal, lightVector), 0.0);
        vec4 diffuse = dot_product * lightColor;
        vec4 ambient = ambientStrength * lightColor;

        vec3 view_dir = normalize(camera_pos - ex_worldPosition.xyz);
        vec3 reflect_dir = reflect(-lightVector, world_normal);

        //vec4 color = vec4(0.0, 1.0, 0.0, 0.0);

        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);
        vec4 specular = specularStrength * spec * lightColor; //*color 

        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;

        float distance = length(lightPosition.xyz - ex_worldPosition.xyz);
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));  
        
        ambient  *= attenuation; 
        diffuse  *= attenuation;
        specular *= attenuation;  

        if (dot_product <= 0.0)
        {
            specular = vec4(0, 0, 0, 0);
            out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out);
        }
        else
        {
            out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out);
        }
    }

    if (typeLight == 2)
    {
        vec3 world_normal = normalize(ex_worldNormal);

        vec3 lightVector = normalize(-lightDirection.xyz);

        float dot_product = max(dot(world_normal, lightVector), 0.0);
        vec4 diffuse = dot_product * lightColor;
        vec4 ambient = ambientStrength * objectColor;

        vec3 view_dir = normalize(camera_pos - ex_worldPosition.xyz);
        vec3 reflect_dir = reflect(-lightVector, world_normal);

        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);
        vec4 specular = specularStrength * spec * lightColor;

        if (dot_product <= 0.0)
        {
            specular = vec4(0, 0, 0, 0);
            out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out);
        }
        else
        {
            out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out);
        }
    }
    
    if(typeLight == 3)
    {
        float cutOff = cos(0.09f);
        vec3 world_normal = normalize(ex_worldNormal);
        vec3 lightVector = normalize(lightPosition.xyz - ex_worldPosition.xyz);

        float theta = dot(lightVector, normalize(-lightDirection));

        if(theta > cutOff)
        {
            float dot_product = max(dot(world_normal, lightVector), 0.0);
            vec4 diffuse = dot_product * lightColor;
            vec4 ambient = ambientStrength * lightColor;

            vec3 view_dir = normalize(camera_pos - ex_worldPosition.xyz);
            vec3 reflect_dir = reflect(-lightVector, world_normal);

            float spec = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);
            vec4 specular = specularStrength * spec * lightColor;

            if (dot_product <= 0.0)
            {
                specular = vec4(0, 0, 0, 0);
                out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out);
            }
            else
            {
                out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out);
            }
        }
        else
        {
            vec4 ambient = ambientStrength * lightColor;
            out_Color = ambient * texture(textureUnitID, vt_out);
        }
    }

    if (typeLight == 4)
    {
        if (light_on == 1)
        {
            float outerCutOff = cos(0.22f);
            float cutOff = cos(0.2f);
            vec3 world_normal = normalize(ex_worldNormal);
            vec3 lightVector = normalize(camera_pos - ex_worldPosition.xyz);

            float theta = dot(lightVector, normalize(-camera_dir));
            float epsilon = cutOff - outerCutOff;
            float intensity = smoothstep(outerCutOff, cutOff, theta);

            if(theta > cutOff)
            {
                float dot_product = max(dot(world_normal, lightVector), 0.0);
                vec4 diffuse = dot_product * lightColor;
                vec4 ambient = ambientStrength * lightColor;

                vec3 reflect_dir = reflect(-lightVector, world_normal);

                float spec = pow(max(dot(lightVector, reflect_dir), 0.0), shininess);
                vec4 specular = specularStrength * spec * lightColor;

                float constant = 1.0f;
                float linear = 0.09f;
                float quadratic = 0.032f;

                float distance = length(camera_pos - ex_worldPosition.xyz);
                float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
                                
                diffuse  *= intensity;
                specular *= intensity; 

                ambient  *= attenuation; 
                diffuse  *= attenuation;
                specular *= attenuation;  

                if (dot_product <= 0.0)
                {
                    specular = vec4(0, 0, 0, 0);
                    out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out) ;
                }
                else
                {
                    out_Color = (ambient + diffuse + specular) * texture(textureUnitID, vt_out) ;
                }
            }
            else
            {
                vec4 ambient = ambientStrength * lightColor;
                out_Color = ambient * texture(textureUnitID, vt_out);
            }
        }
        if (light_on == 0)
        {
            vec4 ambient = ambientStrength * lightColor;
            out_Color = ambient * texture(textureUnitID, vt_out);
        }
    }
}