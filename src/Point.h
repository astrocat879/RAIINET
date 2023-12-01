#ifndef __POINT_H__
#define __POINT_H__

struct Point{
    int y, x;

    Point operator +(Point other) {
        return Point{y+other.y, x+other.x};
    }
};

#endif
