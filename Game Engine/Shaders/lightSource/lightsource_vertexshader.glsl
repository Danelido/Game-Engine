#version 330

layout ( location = 0 ) in vec4 light_position;
layout ( location = 1 ) in vec4 light_color;


uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;


out LIGHT_DATA {

	vec4 light_color;

} light_vs_out;

void main()
{
	gl_Position =  projection_matrix * view_matrix * model_matrix * vec4(light_position.x, light_position.y, light_position.z, 1.0f);
	light_vs_out.light_color = light_color;

}