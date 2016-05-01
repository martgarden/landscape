#version 330

out vec4 final_color;

in vec3 VS_normal_ws;
in vec3 VS_position_ws;

uniform vec3 fog_color;
uniform float fog_density;
uniform vec3 eye_pos;

layout (std140) uniform light_data {
    vec4 position;
    vec3 ambient;
    vec3 diffuse;
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
    vec3 material_ambient = vec3(1.0, 1.0, 1.0);
    vec3 material_diffuse = vec3(1.0, 1.0, 1.0);
    vec3 material_specular = vec3(1.0, 1.0, 1.0);
    float material_shininess = 0.05;
    vec3 L, E, N, H;
    E = normalize(eye_position - VS_position_ws);
    N = normalize(VS_normal_ws);
    float Idiff, Ispec;
    vec3 light = vec3(0.0);
    //for(int i = 0; i < 4; i++) {
        L = normalize(lights[0].position.xyz - lights[0].position.w*VS_position_ws);
        H = normalize(E + L);

        Idiff = max(dot(L, N), 0.0);
        Ispec = (Idiff * pow(max(dot(H, N), 0.0), material_shininess));

        light += material_ambient * lights[0].ambient +
        material_diffuse * lights[0].diffuse * Idiff +
        material_specular * lights[0].specular * Ispec;
    //}

    final_color = vec4(light, 1.0);
}
