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
    float dist = (1 - acos(dot(normalize(sun_pos), normalize(VS_tex_coord_ws)))/3.1415);
    vec3 ssun_color = 0.3 * (sun_color.r+sun_color.g+sun_color.b) * texture(day_tex, VS_tex_coord_ws).rgb;
    vec3 mmoon_color = 0.3 * (moon_color.r+moon_color.g+moon_color.b) * texture(night_tex, VS_tex_coord_ws).rgb;
    final_color = vec4(mix(ssun_color, sun_color, dist*0.4+0.6*smoothstep(0.96, 0.98, dist)) +
                       mix(mmoon_color, moon_color, (1-dist)*0.05+0.95*smoothstep(0.97, 0.99, 1-dist)), 1.0);
}
