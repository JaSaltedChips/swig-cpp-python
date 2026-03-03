#ifndef POINT_H
#define POINT_H

struct Point {
    int x;
    int y;
};

Point make_point(int x, int y);
Point add_points(Point a, Point b);
Point scale_point(Point p, int factor);
int manhattan_length(Point p);

#endif
