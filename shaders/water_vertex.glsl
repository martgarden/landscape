#version 330

in vec2 position;

uniform float water_level;
uniform mat4 pv_matrix;

out vec3 VS_position_ws;
out vec4 VS_screen_pos_ws;

void main()
{
    vec4 wposition = vec4(position.x, water_level, position.y, 1.0);
    VS_position_ws = wposition.xyz;
    VS_screen_pos_ws = pv_matrix * wposition;
    gl_Position = VS_screen_pos_ws;
    gl_ClipDistance[0] = 1.0;
}
