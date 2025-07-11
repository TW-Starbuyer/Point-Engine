![Logo](assets/icons/PointLogoLightTransparentBanner.png)

## About:
Point is a toy 3D game engine created by Taylor Wolff as their undergraduate capstone project.

## Features:
* A 3D renderer with [OpenGL](https://www.opengl.org)
* Window/Input management with [SDL3](https://libsdl.org)
* Custom materials system with shader compilation.
* A custom resource manager for caching textures/materials.
* gltf/glb model loading with [Assimp](https://www.assimp.org)
* A custom entity component system using the sparse/dense set design pattern.
* Fast mathematics with the [OpenGL Mathematics Library (GLM)](https://github.com/g-truc/glm)
* Native C++ scripting.

## Installation:
You can install the engine by cloning the repository, there are currently two different versions, the OOP version will be deleted in the future, the only active and ongoing version is the OpenGL-DOD branch.

## Building:
The engine uses the [CMake](https://cmake.org) build system for portable building across architectures. Currently building for the OpenGL-DOD build has only been tested on an x86 Intel CPU with Windows 11. Other architectures will be tested soon, but no other OS is planned to be supported. To build the project just build the target "Engine.exe". If any packages aren't found automatically then CMake's fetch command will retrieve them.

## Assets
All distributed assets for the engine are licensed under creative commons licenses:

Utah teapot model:
https://sketchfab.com/3d-models/the-utah-teapot-1092c2832df14099807f66c8b792374d

Grass texture:
https://flic.kr/p/3irSi4

Dirty metal texture:
https://flic.kr/p/bcCbkX


