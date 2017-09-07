#include <stdio.h>
#include <stdlib.h>

#include "glfw_i.h"

  //////////////
 /// STATIC ///
//////////////

static GLFWwindow* win;

static void on_error       (int error, const char* description);
static void on_key         (GLFWwindow* window, int key, int scancode, int action, int mods);
static void on_mouse_move  (GLFWwindow* window, double xpos, double ypos);
static void on_mouse_button(GLFWwindow* window, int button, int action, int mods);
static void on_scroll      (GLFWwindow* window, double xoffset, double yoffset);

static void
_init() {
    
    printf("GLFW %d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

    glfwSetErrorCallback(on_error);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    win = glfwCreateWindow(800, 800, "DIG", NULL, NULL);
    if (!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback        (win, on_key         );
    glfwSetScrollCallback     (win, on_scroll      );
    glfwSetCursorPosCallback  (win, on_mouse_move  );
    glfwSetMouseButtonCallback(win, on_mouse_button);

    glfwMakeContextCurrent(win);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
}

static void
_free() {
    glfwDestroyWindow(win);
    glfwTerminate();
}

static void
_loop(void(*loop)()){
    while (!glfwWindowShouldClose(win)) {

        // float ratio;
        int width, height;

        glfwGetFramebufferSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        loop();    
        
        glfwPollEvents();
        glfwSwapBuffers(win);
    }

}

static void
on_error(int error, const char* description) {
}

static void
on_key(GLFWwindow* win, int key, int scancode, int action, int mods) {

    // if(*scene.on_key != NULL) {
    //     scene.on_key(key, scancode, action, mods);
    // }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GLFW_TRUE);
}

static void
on_mouse_move(GLFWwindow* win, double xpos, double ypos) {
    // if(*scene.on_mouse_move != NULL){ 
    //     scene.on_mouse_move(xpos, ypos) ;
    // };
}

static void 
on_mouse_button(GLFWwindow* win, int button, int action, int mods) {
    // if(*scene.on_mouse_button != NULL){ 
    //     scene.on_mouse_button(button, action, mods);
    // };
}

static void 
on_scroll(GLFWwindow* win, double xoffset, double yoffset) {
    // if(*scene.on_scroll != NULL){ 
    //     scene.on_scroll(xoffset, yoffset);
    // };
}

  //////////////
 /// GLOBAL ///
//////////////

glfw_i glfw = {
    .win  = &win,
    .free = _free,
    .init = _init,
    .loop = _loop,
};