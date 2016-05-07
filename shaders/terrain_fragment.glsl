#version 330

out vec4 final_color;

in vec3 VS_normal_ws;
in vec3 VS_position_ws;
in vec2 VS_tex_coord_ws;

uniform vec3 fog_color;
uniform float fog_density;
uniform vec3 eye_pos;
uniform sampler2D brgb_map;
uniform sampler2D background_tex;
uniform sampler2D red_tex;
uniform sampler2D green_tex;
uniform sampler2D blue_tex;

struct light_struct {
    vec4 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

uniform vec3 eye_position;

void main()
{
    vec2 tiled_tex_coord = 5.0 * VS_tex_coord_ws;
    vec4 brgb = texture(brgb_map, VS_tex_coord_ws);
    float background_level = 1-(brgb.r + brgb.g + brgb.b);
    vec3 material_ambient = (texture(background_tex, tiled_tex_coord) * background_level +
                             texture(red_tex, tiled_tex_coord) * brgb.r +
                             texture(green_tex, tiled_tex_coord) * brgb.g +
                             texture(blue_tex, tiled_tex_coord) * brgb.b).rgb;
    vec3 material_diffuse = material_ambient;
    vec3 material_specular = vec3(1.0, 1.0, 1.0);
    float material_shininess = 100.0;
    vec3 L, E, N, H;
    E = normalize(eye_position - VS_position_ws);
    N = normalize(VS_normal_ws);
    float Idiff, Ispec;
    vec3 light = vec3(0.0);
    for(int i = 0; i < no_lights; i++) {
        L = normalize(lights.light_data[light_indices[i]].position.xyz - lights.light_data[light_indices[i]].position.w*VS_position_ws);
        H = normalize(E + L);

        Idiff = max(dot(L, N), 0.0);
        Ispec = (Idiff * pow(max(dot(H, N), 0.0), material_shininess));

        light += material_ambient * lights.light_data[light_indices[i]].ambient +
        material_diffuse * lights.light_data[light_indices[i]].diffuse * Idiff +
        material_specular * lights.light_data[light_indices[i]].specular * Ispec;
    }

    final_color = vec4(light, 1.0);
}
