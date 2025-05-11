#version 460 core

out vec4 fragColor;

in SHADER_VARIABLES
{
    vec2 texCoords;
} fs_variables;

// Star parameters
float gridSize = 50.0;    
float starRadius = 0.005; 
float starDensity = 0.001;

uniform float time;
//uniform float speed;

float hash(vec2 p) {
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    vec2 texCoord = fs_variables.texCoords/vec2(0.16, 0.9);
	texCoord = texCoord+vec2(0, -0.8*time);
    vec2 baseCell = floor(texCoord * gridSize);
    
    // Check 3x3 neighborhood around current cell
    for(float dx = -1.0; dx <= 1.0; dx += 1.0) {
        for(float dy = -1.0; dy <= 1.0; dy += 1.0) {
            vec2 cell = baseCell + vec2(dx, dy);
            
            float randVal = hash(cell);
            if(randVal < starDensity) {
                // Generate star position (consistent across cells)
                vec2 starCenter = (cell + 0.5 + vec2(
                    hash(cell + vec2(1.0, 2.0)) - 0.5,
                    hash(cell + vec2(3.0, 4.0)) - 0.5
                )) / gridSize;

                // Calculate distance to potential star
                float dist = distance(texCoord, starCenter);
                if(dist < starRadius) {
                    fragColor = vec4(1.0);
                    return; // Early exit if star found
                }
            }
        }
    }
    
    // If no stars found, black background
    fragColor = vec4(0.0, 0.0, 0.0, 1.0);
}