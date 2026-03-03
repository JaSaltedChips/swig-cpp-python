#include "point.h"

Point make_point(int x, int y) {
    return Point{x, y};
}

Point add_points(Point a, Point b) {
    return Point{a.x + b.x, a.y + b.y};
}

Point scale_point(Point p, int factor) {
    return Point{p.x * factor, p.y * factor};
}

int manhattan_length(Point p) {
    return (p.x >= 0 ? p.x : -p.x) + (p.y >= 0 ? p.y : -p.y);
}
