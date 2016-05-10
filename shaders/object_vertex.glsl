#version 330

in vec4 position;
in vec3 normal;
in vec2 tex_coord;

uniform vec4 clip_plane;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;
uniform mat4 pvm_matrix;

out vec3 VS_normal_ws;
out vec3 VS_position_ws;
out vec2 VS_tex_coord_ws;

void main()
{
    VS_normal_ws = normalize(normal_matrix * normal);
    vec4 moved = model_matrix * position;
    VS_position_ws = moved.xyz;
    VS_tex_coord_ws = tex_coord;
    gl_Position = pvm_matrix * position;
    gl_ClipDistance[0] = dot(moved, clip_plane);
}
