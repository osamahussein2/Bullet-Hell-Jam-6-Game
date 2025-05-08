#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoords;

out SHADER_VARIABLES
{
    vec2 texCoords;
} vs_variables;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vs_variables.texCoords = textureCoords;
    gl_Position = projectionMatrix * modelMatrix * vec4(position, 0.0, 1.0);
}