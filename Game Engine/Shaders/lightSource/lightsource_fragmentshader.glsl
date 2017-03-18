#version 330

layout ( location = 0 ) out vec4 light_color;


in LIGHT_DATA 
{

	vec4 light_color;

} light_fs_in;


void main()
{
	light_color = light_fs_in.light_color;

}