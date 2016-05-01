#version 330

out vec4 final_color;

in vec3 VS_normal_ws;
in vec3 VS_position_ws;

uniform vec3 fog_color;
uniform float fog_density;
uniform vec4 eye_pos;

uniform light_data {
    vec4 position;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
} lights[4];

/*
uniform vec3 material_ambient;
uniform vec3 material_diffuse;
uniform vec3 material_specular;
uniform float material_shininess;
*/

uniform vec3 eye_position;

void main()
{
    /*vec3 L;
    if(light_position.w == 0)
        L = normalize(light_position.xyz);
    else
        L = normalize(light_position.xyz - VS_position_ws);

    vec3 E = normalize(eye_position - VS_position_ws);
    vec3 N = normalize(VS_normal_ws);
    vec3 H = normalize(E + L);

    float Idiff = max(dot(L, N), 0.0);
    float Ispec = (Idiff * pow(max(dot(H, N), 0.0), material_shininess));

    vec3 light = material_ambient * light_ambient +
        material_diffuse * light_diffuse * Idiff +
        material_specular * light_specular * Ispec;

    if(light2_position.w == 0)
        L = normalize(light2_position.xyz);
    else
        L = normalize(light2_position.xyz - VS_position_ws);

    E = normalize(eye_position - VS_position_ws);
    N = normalize(VS_normal_ws);
    H = normalize(E + L);

    float Idiff2 = max(dot(L, N), 0.0);
    float Ispec2 = (Idiff * pow(max(dot(H, N), 0.0), material_shininess));

    vec3 light2 = material_ambient * light2_ambient +
        material_diffuse * light2_diffuse * Idiff2 +
        material_specular * light2_specular * Ispec2;

    final_color = vec4(light + light2, 1.0);*/
    final_color = vec4(1.0);
}
