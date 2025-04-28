#version 460 core

out vec4 fragColor;

in SHADER_VARIABLES
{
	vec2 texCoords;

} fs_variables;

uniform sampler2D spriteImage;
uniform vec3 spriteColor;

uniform int columns;
uniform int rows;
uniform int frame;

uniform int hor_flip;
uniform int vert_flip;

void main()
{
	vec2 frame_size = 1.0/vec2(columns, rows); // size of one tile
	vec2 frame_tex = fs_variables.texCoords*frame_size;
	
	vec2 uv = vec2(1.0 - frame_tex.x, frame_tex.y);
	// conditional flip
	uv.x = hor_flip*frame_size.x - (hor_flip*2-1)*uv.x;
	uv.y = vert_flip*frame_size.y - (vert_flip*2-1)*uv.y;

	int col = frame % columns;
	int row = frame / columns;

	uv += vec2(col, row) * frame_size;

	// Set the color of the sprite by multiplying sprite color with the texture
	fragColor = vec4(spriteColor, 1.0) * texture(spriteImage, uv);
}