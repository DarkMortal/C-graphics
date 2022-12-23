#ifndef LINE
#define LINE

#include <iostream>
#include <graphics.h>

class Point{
    public: uint16_t x,y;
    Point(uint16_t&& a,uint16_t&& b):x(a),y(b){}  // Using R-value reference to save memory
};

class Line{
    float m,c;
    
    public: Point p1,p2;
    uint16_t minX,maxX,minY,maxY;
    Line(Point&&,Point&&);  // Using R-value reference to save memory

    float getX(float y) const { return (y+c)/m; }
    float getY(float x) const { return m*x+c; }
    void drawLine(){ line(p1.x, p1.y, p2.x, p2.y); }
};

Line::Line(Point&& a,Point&& b):p1(a),p2(b){
    m = ( (float)(p1.y) - (float)(p2.y) ) / ( (float)(p1.x) - (float)(p2.x) );
    c = (float)(p1.y) - m * (float)(p1.x);

    minX = (a.x>b.x)?b.x:a.x;
    maxX = (minX == a.x)?b.x:a.x;

    minY = (a.y>b.y)?b.y:a.y;
    maxY = (minY == a.y)?b.y:a.y;
}

#endif //LINE