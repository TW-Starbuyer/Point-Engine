#version 330 core
layout (location = 0) in vec3 position; 
layout (location = 1) in vec3 color; 
layout (location = 2) in vec2 texture;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_Projection;
uniform float u_TextureRepeatScale;

out vec3 ourColor;
out vec3 texture_coordinates;


void main()
{
      vec4 newPosition = u_Projection * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0f);
        
      gl_Position = newPosition;  

      ourColor = color;
      
      texture_coordinates = vec3(texture * u_TextureRepeatScale, 0.0);
      
     
}