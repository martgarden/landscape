#version 330

in vec2 position;

uniform mat4 pv_matrix;
uniform sampler2D height_map;

out vec3 VS_normal_ws;
out vec3 VS_position_ws;
out vec2 VS_tex_coord_ws;

void main()
{
    vec4 scale = vec4(200.0, 80.0, 200.0, 1.0);
    vec4 final_pos = scale * vec4(position.x, texture(height_map, position).r, position.y, 1.0);
    VS_normal_ws = vec3(0.0, 1.0, 0.0);
    VS_position_ws = final_pos.xyz;
    VS_tex_coord_ws = position;
    gl_Position = pv_matrix * final_pos;
}
