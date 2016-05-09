#version 330

in vec2 position;

uniform mat4 pv_matrix;
uniform sampler2D height_map;
uniform int x_off;
uniform int z_off;

out vec3 VS_normal_ws;
out vec3 VS_position_ws;
out vec2 VS_tex_coord_ws;

void main()
{
    vec2 tex_coords = vec2(1 - position.x, position.y);
    vec2 res_x = vec2(0.01, 0.0);
    vec2 res_z = vec2(0.0, 0.01);
    vec4 scale = vec4(200.0, 140.0, 200.0, 1.0);
    vec4 final_pos = scale * vec4(position.x + x_off, texture(height_map, tex_coords).r, position.y + z_off, 1.0);
    vec3 x_nor = normalize(vec3(texture(height_map, tex_coords+res_x).r - texture(height_map, tex_coords-res_x).r, res_x.x*2, 0.0));
    vec3 z_nor = normalize(vec3(0.0, res_z.y*2, texture(height_map, tex_coords-res_z).r - texture(height_map, tex_coords-res_z).r));
    VS_normal_ws = scale.xyz * (x_nor + z_nor);
    VS_position_ws = final_pos.xyz;
    VS_tex_coord_ws = tex_coords;
    gl_Position = pv_matrix * final_pos;
}
