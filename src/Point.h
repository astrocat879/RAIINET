#ifndef __POINT_H__
#define __POINT_H__
#include <string>
using namespace std;

struct Point{
    int y, x;

    Point operator +(Point other) {
        return Point{y+other.y, x+other.x};
    }

    bool operator ==(Point other) {
        return (y==other.y) && (x==other.x);
    }
    
    bool outOfBounds(Point up, Point right, Point botLeft){
        int y = botLeft.y * up.y;
        int x = botLeft.x * right.x;
        if (x < 0 || x > 7 || y < 0) {
            return true;
        }
        return false;
    }

    bool inDownloadZone(Point up, Point right, Point botLeft){
        int y = botLeft.y * up.y;
        int x = botLeft.x * right.x;
        if (y > 7) {
            return true;
        }
        return false;
    }

    static Point translate(string dir) {
        if (dir == "up") {
            return Point{1, 0};
        }
        else if (dir == "right") {
            return Point{0, 1};
        }
        else if (dir == "down") {
            return Point{-1, 0};
        }
        else if (dir == "left") {
            return Point{0, -1};
        }
    }
};

#endif
