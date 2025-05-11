#version 100
precision highp float;

varying vec2 texCoords;

uniform sampler2D spriteImage;
uniform vec3 spriteColor;

uniform int columns;
uniform int rows;
uniform int frame;

uniform int hor_flip;
uniform int vert_flip;

void main() {
    vec2 frame_size = 1.0 / vec2(float(columns), float(rows));
    vec2 frame_tex = texCoords * frame_size;

    vec2 uv = vec2(1.0 - frame_tex.x, frame_tex.y);
    // conditional flip
    uv.x = float(hor_flip) * frame_size.x - (float(hor_flip) * 2.0 - 1.0) * uv.x;
    uv.y = float(vert_flip) * frame_size.y - (float(vert_flip) * 2.0 - 1.0) * uv.y;

    // Frame calculation
    int col = int(mod(float(frame), float(columns)));
    int row = frame / columns;
    uv += vec2(float(col), float(row)) * frame_size;

    // Texture sampling (must use texture2D)
    gl_FragColor = vec4(spriteColor, 1.0) * texture2D(spriteImage, uv);
}