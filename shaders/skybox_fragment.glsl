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
    final_color = texture(day_tex, VS_tex_coord_ws);
}
