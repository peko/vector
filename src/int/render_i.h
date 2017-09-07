#pragma once

#include "scene_i.h"

typedef struct {

    // interface
    void (*init)();
    void (*free)();

    void (*draw)(scene_i* scene);

} render_i;