#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture2d;
uniform vec3 _color;

void main() {
	FragColor = texture(texture2d, TexCoord) * vec4(_color, 1.0);
}