#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

#include "Shader.h"
#include "Audio.h"
#include "MultiSound.h"
#include "Music.h"

class ResourceManager
{
public:

    // resource storage
    static map<int, Shader> shaders;
    static map<int, unsigned int> textures;
    static map<int, Music> music;
    static map<int, MultiSound> sounds;

    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
    // If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, int enum_);

    // Retrieves a stored sader
    static Shader GetShader(int enum_);

    // Loads (and generates) a texture from file
    static unsigned int LoadTexture(const char* file, int enum_);

    // Retrieves a stored texture
    static unsigned int GetTexture(int enum_);

    static Music* LoadMusic(const char* file, int enum_);
    static Music* GetMusic(int enum_);

    static MultiSound* LoadSound(const char* file, int enum_);
    static MultiSound* GetSound(int enum_);

    static void ApplyMusicVolume(float volume);
    static void ApplySfxVolume(float volume);

    static int currentMusic;

    static void PlayMusic(int enum_, bool force_new_ = false);
    static void StopMusic();
    static void ResumeMusic();

    // Properly de-allocates all loaded resources
    static void Clear();

private:

    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }

    static GLenum format;
};

#endif //RESOURCE_MANAGER_H