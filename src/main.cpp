#include "mesh.hpp"
#include "shaders.hpp"
#include "util.hpp"

#include <glad/gles2.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdio>
#include <functional>
#include <stack>
#include <vector>

static std::stack<std::function<void()>> defer;

GLFWwindow* window = nullptr;

int main() {
    if (glfwInit() != GLFW_TRUE) {
        return 1;
    }
    defer.push([] { glfwTerminate(); });

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(800, 600, "Editor", nullptr, nullptr);
    if (window == nullptr) {
        return 2;
    }
    defer.push([] { glfwDestroyWindow(window); });

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGLES2(glfwGetProcAddress);

    initShaders();
    auto tileMesh = new TileMesh();

    GLfloat pvMatrix[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
    };

    GLfloat modelMatrix[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
    };

    auto f = new Framebuffer {
        .maxWidth = 1920,
        .maxHeight = 1080,
        .format = TF_RGBA8_UINT,
    };
    f->init(nullptr);

    std::vector<GLubyte> buf(1024 * 1024 * 4);
    long id = 0;
    for (long rank = 0; rank < 6; rank++) {
        long offset = 4 * (1024 * (id & 1023) + 200 * rank + (id >> 10));
        buf[offset + 0] = 255;
        buf[offset + 1] = 0;
        buf[offset + 2] = 0;
        buf[offset + 3] = 255;
    }
    id = 1024;
    for (long rank = 0; rank < 6; rank++) {
        long offset = 4 * (1024 * (id & 1023) + 200 * rank + (id >> 10));
        buf[offset + 0] = 0;
        buf[offset + 1] = 255;
        buf[offset + 2] = 0;
        buf[offset + 3] = 255;
    }

    auto t = new Texture {
        .width = 1024,
        .height = 1024,
        .format = TF_RGBA8_UNORM,
        .magFilter = GL_NEAREST,
        .minFilter = GL_NEAREST,
        .wrapS = GL_TEXTURE_WRAP_S,
        .wrapT = GL_TEXTURE_WRAP_T,
    };
    t->init(buf.data());

    while (true) {
        glfwPollEvents();

        if (glfwWindowShouldClose(window)) {
            break;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, 800, 600);
        glScissor(0, 0, 800, 600);

        glClearColor(0.1, 0.3, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        mapTileShader::bind();
        mapTileShader::pvMatrix(pvMatrix);
        mapTileShader::modelMatrix(modelMatrix);
        t->bind(0);
        mapTileShader::map_tile(0);
        tileMesh->bind();
        tileMesh->draw();

        glfwSwapBuffers(window);
    }

    while (!defer.empty()) {
        defer.top()();
        defer.pop();
    }

    return 0;
}
