#include <math.h>
#include <stdio.h>

#include "scene_i.h"
#include "kvec.h"

  //////////////
 /// STATIC ///
//////////////

static vbo_p vbo;
static cam_p cam;
static cam_t _cam = {
    .x = 0.0,
    .y = 0.0,
    .s = 1.0,
    .r = 1.0
};

static GLFWwindow* win;

// interaface
static void 
_init(GLFWwindow* window) {
    
    win = window;

    cam = &_cam;
    vbo = vbo_new();    

    // alloc ten parts by ten points
    parts_v parts;
    kv_init(parts);
    for(int i=0; i<33; i++) {
        points_v points;
        kv_init(points);
        float d=8.0;
        for(int j=0; j<d; j++) {
            point_t p = (point_t) {
                sin(j/d*3.141*2.0+i/64.0*3.141)/(i/5.0+1.0), 
                cos(j/d*3.141*2.0+i/64.0*3.141)/(i/5.0+1.0)};
            kv_push(point_t, points, p);
        }
        kv_push(points_v, parts, points);
    }

    // fill vbo
    vbo_fill(vbo, &parts);
    
    // free parts
    for(int i=0; i<10; i++ ) kv_destroy(parts.a[i]);
    kv_destroy(parts);
};

static void 
_update(){
};

static void 
_draw(){
};

static void 
_free() {
    vbo_free(vbo);
};

// Interactive handlers
static void on_key (int key, int scancode, int action, int mods){
    
    printf("a: %d k: %d\n", action, key);
    
    float step = 0.1;
    if(action > 0)
    switch(key) {

        // move
        case GLFW_KEY_KP_4:
        case GLFW_KEY_LEFT:
            cam->x-=step;
            break;
        case GLFW_KEY_KP_6:
        case GLFW_KEY_RIGHT:
            cam->x+=step;
            break;
        case GLFW_KEY_KP_8:
        case GLFW_KEY_UP:
            cam->y+=step;
            break;
        case GLFW_KEY_KP_2:
        case GLFW_KEY_DOWN:
            cam->y-=step;
            break;
        
        // zoom
        case GLFW_KEY_KP_SUBTRACT:
            cam->s/=2.0;
            break;
        case GLFW_KEY_KP_ADD:
            cam->s*=2.0;
            break;
    };
};

static void on_mouse_move  (double xpos, double ypos){};
static void on_scroll      (double xoffset, double yoffset){};
static void on_mouse_button(int button, int action, int mods){};

  //////////////
 /// GLOBAL ///
//////////////

scene_i scene_hexagons = {
    
    .vbo = &vbo,
    .cam = &cam,

    //interface
    .init   = _init,
    .update = _update,
    .draw   = _draw,
    .free   = _free,

    // events
    .on_key          = on_key,
    .on_mouse_move   = on_mouse_move,
    .on_scroll       = on_scroll,
    .on_mouse_button = on_mouse_button
};
