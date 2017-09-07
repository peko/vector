
#include "glfw_i.h"
// #include "gui_i.h"
#include "scene_i.h"
#include "render_i.h"

extern glfw_i   glfw;
// extern gui_i    gui_master;
extern render_i render_wire;
extern scene_i  scene_hexagons;

// static gui_i    gui;
static scene_i  scene;
static render_i render;

static void loop();

int
main(int argc, char** argv) {

    glfw.init();
    
    render = render_wire;
    render.init();

    scene = scene_hexagons;
    scene.init(*glfw.win);

    // gui = gui_master;
    // gui.init(*glfw.win);

    glfw.loop(loop);

    scene.free();
    render.free();
    // gui.free();

    glfw.free();

    exit(EXIT_SUCCESS);    
};

static void 
loop() {
    scene.update();
    render.draw(&scene);
    // gui.update();
    // gui.draw();
}
