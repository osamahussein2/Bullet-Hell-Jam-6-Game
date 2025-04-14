#version 460 core

out vec4 fragColor;

in SHADER_VARIABLES
{
	vec2 texCoords;

} fs_variables;

uniform sampler2D spriteImage;
uniform vec3 spriteColor;

void main()
{
	// Set the color of the sprite by multiplying sprite color with the texture
	//fs_variables.texCoords = vec2(1.0-fs_variables.texCoords.x, fs_variables.texCoords.y);
	vec2 uv = vec2(1.0-fs_variables.texCoords.x, fs_variables.texCoords.y);
	fragColor = vec4(spriteColor, 1.0) * texture(spriteImage, uv);
}