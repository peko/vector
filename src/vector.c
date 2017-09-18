
#include "int/glfw_i.h"
#include "int/scene_i.h"
#include "int/render_i.h"

extern glfw_i   glfw;
// extern gui_i    gui_master;
extern render_i render_wire;
extern scene_i  scene_hexagons;

// static gui_i    gui;
static scene_i  scene;
static render_i render;

void vector_init() {

    glfw.init();
    
    render = render_wire;
    render.init();

    scene = scene_hexagons;
    scene.init(*glfw.win);

    // gui = gui_master;
    // gui.init(*glfw.win);

}

static void loop() {
    scene.update();
    render.draw(&scene);
    // gui.update();
    // gui.draw();
}

void vector_loop() {

    glfw.loop(loop);

}

void vector_exit() {
	
    scene.free();
    render.free();
    // gui.free();

    glfw.free();

}

