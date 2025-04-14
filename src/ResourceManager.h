#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

#include "Shader.h"

class ResourceManager
{
public:

    // resource storage
    static map<int, Shader> shaders;
    static map<int, unsigned int> textures;

    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
    // If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, int enum_);

    // Retrieves a stored sader
    static Shader GetShader(int enum_);

    // Loads (and generates) a texture from file
    static unsigned int LoadTexture(const char* file, int enum_);

    // Retrieves a stored texture
    static unsigned int GetTexture(int enum_);

    // Properly de-allocates all loaded resources
    static void Clear();

private:

    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }

    static GLenum format;
};

#endif //RESOURCE_MANAGER_H