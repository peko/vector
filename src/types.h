#pragma once

#include "kvec.h"

/// vector of strings
typedef kvec_t(char*) strings_v;
void strings_destroy(strings_v* str);

/// simple point
typedef struct {
    double x, y;
} point_t;

/// vector of points (contour / shape part part)
typedef kvec_t(point_t) shape_v;
void shape_destroy(shape_v* s);

// multiple contours (country with islands)
typedef struct {
    kvec_t(shape_v);
    point_t min, max, center;
} shapes_v;
void shapes_destroy(shapes_v* s);

/// multiple multiple contours (countries)
typedef kvec_t(shapes_v) countries_v;
void countries_destroy(countries_v* s);
