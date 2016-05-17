#version 330

out vec4 final_color;

in vec3 VS_position_ws;
in vec4 VS_screen_pos_ws;

uniform vec3 fog_color;
uniform float fog_density;
uniform vec3 eye_position;
uniform float day_time;
uniform sampler2D reflect_tex;
uniform sampler2D refract_tex;

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

float random (in vec2 st) { 
    return fract(sin(dot(st.xy,
        vec2(12.9898,78.233)))
        * 43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    return mix(a, b, u.x) + 
        (c - a)* u.y * (1.0 - u.x) + 
        (d - b) * u.x * u.y;
}

void main()
{
    vec2 tex_coord = (VS_screen_pos_ws.xy / VS_screen_pos_ws.w)/2 + vec2(0.5, 0.5);
    vec2 dudv = 0.05 * vec2(noise(VS_position_ws.xz + day_time), noise(VS_position_ws.xz + vec2(1.0, 1.0) - 0.5*day_time));
    vec2 refl_coord = vec2(tex_coord.x, 1.0-tex_coord.y);
    vec3 color = mix(texture(reflect_tex, refl_coord + dudv).rgb, texture(refract_tex, tex_coord.xy + dudv).rgb, 0.5);
    vec3 water_specular = vec3(1.0, 1.0, 1.0);
    float water_shininess = 1000.0;
    vec3 L, E, N, H;
    E = normalize(eye_position - VS_position_ws);
    N = vec3(-dudv.x, 1.0, -dudv.y);
    float Ispec;
    for(int i = 0; i < no_lights; i++) {
        L = normalize(lights.light_data[light_indices[i]].position.xyz - lights.light_data[light_indices[i]].position.w*VS_position_ws);
        H = normalize(E + L);

        Ispec = max(dot(L, N), 0.0) * pow(max(dot(H, N), 0.0), water_shininess);

        color += water_specular * lights.light_data[light_indices[i]].specular * Ispec;
    }

    final_color = vec4(mix(color, fog_color, 1.0-clamp(exp(-fog_density*length(eye_position - VS_position_ws)), 0.0, 1.0)), 1.0);
}
