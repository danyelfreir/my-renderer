#version 120

struct PositionLight {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 ambient;
};

struct Material {
    vec4 diffuse;
    vec4 specular;
    vec4 ambient;
    float shininess;
};

uniform PositionLight u_position_light;
uniform Material u_material;
uniform vec4 u_eye_position;

varying vec4 v_normal;
varying vec4 v_position;

void main(void)
{
    vec4 v = normalize(u_eye_position - v_position);

    // Calculate the lighting effect from the spotlight
    vec4 s_spot = normalize(u_position_light.position - v_position);
    vec4 h_spot = normalize(s_spot + v);

    // Diffuse
    float lambert = max(dot(v_normal, s_spot), 0.0);
    vec4 diffuse = u_position_light.diffuse * lambert;

    // Specular
    float phong = max(dot(v_normal, h_spot), 0.0);
    vec4 specular = u_position_light.specular * pow(phong, u_material.shininess);

    // Ambient
    vec4 ambient = u_position_light.ambient;

    // Calculate the lighting effect from the position light
    vec4 s_pos = normalize(u_position_light.position - v_position);
    vec4 h_pos = normalize(s_pos + v);

    // Diffuse
    lambert = max(dot(v_normal, s_pos), 0.0);
    diffuse += u_position_light.diffuse * lambert;

    // Specular
    phong = max(dot(v_normal, h_pos), 0.0);
    specular += u_position_light.specular * phong;

    // Ambient
    ambient += u_position_light.ambient;


    gl_FragColor = (diffuse * u_material.diffuse)
                 + (specular * u_material.specular)
                 + (ambient * u_material.ambient);
}
