/**
* @file shader.cpp
* 
* @brief Programming the shaders that are sent to the GPU to render the application
* 
* @author Aleksander Solhaug
*/

#include <string>
#include <glm/glm.hpp>


const std::string chessBoardShaderSrc = R"(
#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;
out vec2 vsTexCoords;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
out vec2 positionGrid;
void main()
{ 
    positionGrid = position;
    gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 0.0, 1.0);
    vsTexCoords = texCoords;
}
)";

// Fragment shader code
const std::string chessBoardFragmentShaderSrc = R"(
#version 460 core
layout (binding = 0) uniform sampler2D u_Texture;
out vec4 color;
in vec2 vsTexCoords;
in vec2 positionGrid;
uniform vec2 u_selectorPosition;
uniform vec4 u_ColorA;
uniform vec4 u_ColorB;
uniform vec4 u_ColorC;
uniform vec2 u_gridSize;
uniform int u_SetTextures;
float pi = 3.1415926536f;

void main()
{
     if (sin(pi * u_gridSize.y * positionGrid.y) < 0){

        if (sin(pi * u_gridSize.x * positionGrid.x) > 0){
            if(u_SetTextures  == 1){
                color = mix(u_ColorB, texture(u_Texture, vsTexCoords), 0.7f);
            } 
            else {
                color = u_ColorB;
            }   
        }
        else{
            if(u_SetTextures  == 1){
                color = mix(u_ColorA, texture(u_Texture, vsTexCoords), 0.7f);
            } 
            else {
                color = u_ColorA;
            }
        }
    }
    //Colors left right corner white, and right down black
    else  {
        if(sin(pi * u_gridSize.x * positionGrid.x) < 0){
            if(u_SetTextures  == 1){
                color = mix(u_ColorB, texture(u_Texture, vsTexCoords), 0.7f);
            } 
            else {
                color = u_ColorB;
            }
        }
        else {
            if(u_SetTextures  == 1){
                color = mix(u_ColorA, texture(u_Texture, vsTexCoords), 0.7f);
            } 
            else {
                color = u_ColorA;
            }
        }
    }
    //Checking if the selector coordinates are within the square, and offsetting so the selector starts
    //in bottom left corner when program starts 
      if (positionGrid.x < (u_selectorPosition.x + 1.0f)/ u_gridSize.x - (3.5f/u_gridSize.x) && positionGrid.x > u_selectorPosition.x / u_gridSize.x - (3.5f/u_gridSize.x) &&
        positionGrid.y < (u_selectorPosition.y + 1.0f)/ u_gridSize.y - (3.5f/u_gridSize.x) && positionGrid.y > u_selectorPosition.y / u_gridSize.y - (3.5f/u_gridSize.x)){
            if(u_SetTextures  == 1){
                color = mix(u_ColorC, texture(u_Texture, vsTexCoords), 0.7f);
            } 
            else {
                color = u_ColorC;
            }
      }
}
)";

const std::string cubeVertexShaderSrc = R"(
#version 460 core
layout(location = 0) in vec3 position;
out vec3 texCords;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
void main()
{ 
   gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 1.0);
   texCords = position;
}
)";

// Fragment shader code
const std::string cubeFragmentShaderSrc = R"(
#version 460 core
layout(binding = 1) uniform samplerCube u_CubeTexture;
in vec3 texCords;
out vec4 color;
uniform vec4 u_Color;
uniform int u_SetTextures;

void main()
{
    if (u_SetTextures == 1){
        color = mix(u_Color, texture(u_CubeTexture, texCords), 0.7f);
    }
    else {  
        color = u_Color;
    } 
}
)";

