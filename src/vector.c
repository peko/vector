
#include "int/glfw_i.h"
#include "int/scene_i.h"
#include "int/render_i.h"

#include "vector.h"
#include "int/scene_i.h"

extern glfw_i   glfw;
extern render_i render_wire;
extern scene_i  scene_hexagons;

static scene_i  scene;
static render_i render;

void vector_init() {

    glfw.init();
    
    render = render_wire;
    render.init();

    scene = scene_hexagons;
    scene.init(*glfw.win);

}

static void loop() {
    scene.update();
    render.draw(&scene);
}

void vector_loop() {

    glfw.loop(loop);

}

void vector_exit() {
	
    scene.free();
    render.free();
    glfw.free();

}

