#version 100
precision highp float;

attribute vec2 position;
attribute vec2 textureCoords;

varying vec2 texCoords;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main() {
    texCoords = textureCoords;
    gl_Position = projectionMatrix * modelMatrix * vec4(position, 0.0, 1.0);
}