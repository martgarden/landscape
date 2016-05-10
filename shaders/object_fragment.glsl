#version 330

out vec4 final_color;

in vec3 VS_normal_ws;
in vec3 VS_position_ws;
in vec2 VS_tex_coord_ws;

uniform vec3 fog_color;
uniform float fog_density;
uniform vec3 eye_position;
uniform sampler2D color_tex;

struct light_struct {
    vec4 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 attenuation;
};

layout (std140) uniform light_ubo {
    light_struct light_data[20];
} lights;

uniform int no_lights;
uniform int light_indices[20];

/*
uniform vec3 material_ambient;
uniform vec3 material_diffuse;
uniform vec3 material_specular;
uniform float material_shininess;
*/


void main()
{
    float alpha =  texture(color_tex, VS_tex_coord_ws).a;
    vec3 material_ambient = texture(color_tex, VS_tex_coord_ws).rgb;
    vec3 material_diffuse = material_ambient;
    vec3 material_specular = vec3(1.0, 1.0, 1.0);
    float material_shininess = 100.0;
    if(alpha < 0.5)
        discard;
    vec3 L, nL, E, N, H;
    E = normalize(eye_position - VS_position_ws);
    N = normalize(VS_normal_ws);
    float Idiff, Ispec, distance;
    vec3 light = vec3(0.0);
    for(int i = 0; i < no_lights; i++) {
        L = lights.light_data[light_indices[i]].position.xyz - lights.light_data[light_indices[i]].position.w*VS_position_ws;
        distance = length(L);
        nL = normalize(L);
        H = normalize(E + nL);

        Idiff = max(dot(nL, N), 0.0);
        Ispec = (Idiff * pow(max(dot(H, N), 0.0), material_shininess));

        light += (material_ambient * lights.light_data[light_indices[i]].ambient +
        material_diffuse * lights.light_data[light_indices[i]].diffuse * Idiff +
        material_specular * lights.light_data[light_indices[i]].specular * Ispec)/(lights.light_data[light_indices[i]].attenuation.x + distance*lights.light_data[light_indices[i]].attenuation.y + distance*distance*lights.light_data[light_indices[i]].attenuation.z);
    }

    final_color = vec4(mix(light, fog_color, 1.0-clamp(exp(-fog_density*length(eye_position - VS_position_ws)), 0.0, 1.0)), 1.0);
}
