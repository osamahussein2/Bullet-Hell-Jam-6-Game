#include "ResourceManager.h"
#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Instantiate static variables
map<int, Shader> ResourceManager::shaders;
map<int, unsigned int> ResourceManager::textures;

GLenum ResourceManager::format = 0;

Shader ResourceManager::GetShader(int enum_)
{
    if (shaders.find(enum_) == shaders.end())
    {
        cout << "This mapped shader enum is not found: " << enum_ << endl;
    }

    return shaders[enum_];
}

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, int enum_)
{

    // Retrieve the vertex/fragment source code from the shader files
    string vertexCode;
    string fragmentCode;

    try
    {
        // open files
        ifstream vertexShaderFile(vShaderFile);
        ifstream fragmentShaderFile(fShaderFile);
        stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }

    catch (exception e)
    {
        cout << "ERROR::SHADER: Failed to read shader files" << endl;
    }

    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    // Create shader object from source code
    shaders[enum_].InitializeShaders(vertexShaderCode, fragmentShaderCode);

    return shaders[enum_];
}

unsigned int ResourceManager::GetTexture(int enum_)
{
    if (textures.find(enum_) == textures.end())
    {
        cout << "This mapped texture enum is not found: " << enum_ << endl;
    }

    return textures[enum_];
}

unsigned int ResourceManager::LoadTexture(const char* file, int enum_)
{
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    glGenTextures(1, &textures[enum_]);

    if (!data)
    {
        cout << "Can't find texture path at: " << file << endl;
    }

    else if (data)
    {
        // Make sure the number of channels are set to the correct format of image
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;

        // Generate texture
        glBindTexture(GL_TEXTURE_2D, textures[enum_]);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Set the texture wrap and filter modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // nearest for crisp pixelart
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Free image data
        stbi_image_free(data);
    }

    return textures[enum_];
}

void ResourceManager::Clear()
{
    // Delete all shaders properly	
    for (pair<int, Shader> iter : shaders)
    {
        glDeleteProgram(iter.second.shaderProgram);
    }

    // Delete all textures properly
    for (pair<int, unsigned int> iter : textures)
    {
        glDeleteTextures(1, &iter.second);
    }
}