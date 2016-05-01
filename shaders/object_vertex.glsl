#version 330

in vec4 position;
in vec3 normal;
in vec2 tex_coord;

uniform mat4 model_matrix;
uniform mat3 normal_matrix;
uniform mat4 pvm_matrix;

out vec3 VS_normal_ws;
out vec3 VS_position_ws;

void main()
{
    VS_normal_ws = normalize(normal * normal);
    VS_position_ws = (model_matrix * position).xyz;
    gl_Position = pvm_matrix * position;
}
