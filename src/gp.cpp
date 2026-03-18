#include "../include/gp/gp.h"

namespace GP
{
    //glfw: initializes glfw and sets window hints
    void init()
    {
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    //glad: initializes and checks for succcess.
    bool initGLAD()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        return true;
    }

    //glfw: creates window and checks for success.
    GLFWwindow* createWindow(unsigned int width, unsigned int height, const char* title)
    {
        GLFWwindow* window{glfwCreateWindow(width, height, title, NULL, NULL)};
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window\n";
            glfwTerminate();
            //return false;
        }
        //return true;
        return window;
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
}

    Texture2d::Texture2d(const char* path)
    {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        // default parameters
        // set texture wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        unsigned char *data = stbi_load(path, &m_width, &m_height, &m_nrChannels, 0);
        if (data)
        {
            GLenum format {GL_RGB};
            if (m_nrChannels == 4) format = GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture\n";
        }
        stbi_image_free(data);
    }

    void Texture2d::setTexParameter(GLint wrapS, GLint wrapT, GLint minF, GLint maxF)
    {
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minF);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxF);
    }
    unsigned int Texture2d::getObject(){ return m_texture; }