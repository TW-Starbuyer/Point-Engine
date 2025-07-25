#version 330 core

out vec4 FragColor;  

in vec3 ourColor;
in vec3 texture_coordinates;

uniform sampler2D texture1;
  
void main()
{
    FragColor = texture(texture1, texture_coordinates.xy);
}