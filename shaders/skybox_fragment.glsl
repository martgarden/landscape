#version 330

out vec4 final_color;

in vec3 VS_tex_coord_ws;

uniform samplerCube day_tex;
uniform samplerCube night_tex;
uniform vec3 sun_pos;
uniform vec3 sun_color;
uniform vec3 moon_color;

void main()
{
    float dist = (2 - acos(dot(normalize(sun_pos), normalize(VS_tex_coord_ws)))/3.1415)/2;
    vec3 color = 0.3 * (sun_color.r+sun_color.g+sun_color.b) * texture(day_tex, VS_tex_coord_ws).rgb;
    final_color = vec4(mix(color, sun_color, dist*0.4+0.6*smoothstep(0.96, 0.98, dist)), 1.0);
}
