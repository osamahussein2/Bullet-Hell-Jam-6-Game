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
	fragColor = vec4(spriteColor, 1.0) * texture(spriteImage, fs_variables.texCoords);
}