#ifndef SHAPE
#define SHAPE

#include "Vectors.hpp"

#define xOffSet 400
#define yOffSet 300

class Point{
    public:
    int16_t x,y;
    Point* next;
    Point* prev;
    Point(int16_t&& a,int16_t&& b);
    ~Point();
    bool operator == (const Point& p) const noexcept { return (this->x == p.x && this->y == p.y); }
    Vectors operator - (const Point& p) const noexcept { return Vectors(this->x-p.x,this->y-p.y); }
};

Point::Point(int16_t&& a,int16_t&& b):x(a),y(b){
    next = nullptr;
    prev = nullptr;
}

Point::~Point(){}

#endif //SHAPE