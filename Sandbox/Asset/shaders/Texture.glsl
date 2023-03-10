#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjuection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjuection * u_Transform * vec4(a_Position, 1.0 );
}

#type fragment
#version 330 core

layout(location=0) out vec4 color;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

in vec2 v_TexCoord;

void main()
{
	color = mix(texture(u_Texture, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.2);
}
