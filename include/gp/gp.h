#ifndef GP_H
#define GP_H

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include "../stb_image/stb_image.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "../learnopengl/shader_s.h"

#include <iostream>
#include <algorithm>
#include <string>

namespace GP
{
    enum class FileExtension
    {
        png,
        jpg,
        max_extension,
    };

    void init();
    bool initGLAD();
    GLFWwindow* createWindow(unsigned int width, unsigned int height, const char* title);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    constexpr FileExtension getFileExtensionEnum(std::string_view sv);
    FileExtension getFileExtension(const char* filepath);
}

class Texture2d
{
private:
    unsigned int m_texture{};
    int m_width{};
    int m_height{};
    int m_nrChannels{};
public:
    Texture2d(const char* path);
    void setTexParameter(GLint wrapS, GLint wrapT, GLint minF, GLint maxF);
    unsigned int getObject();
};

#endif
