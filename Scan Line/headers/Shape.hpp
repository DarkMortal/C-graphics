#ifndef SHAPE
#define SHAPE

#include <vector>
#include <algorithm>
#include "Line.hpp"

class Shape{
    std::vector<Line> edgeList;

    uint16_t color;

    float minX, maxX;
    float minY, maxY;

    public: Shape(Line* el,uint16_t n,uint16_t c):color(c){
        minX = minY = 1e6;
        maxX = maxY = -1e6;
        for(uint16_t i=0;i<n;i++){
            if(el[i].p1.x>maxX) maxX = el[i].p1.x;
            if(el[i].p2.x>maxX) maxX = el[i].p2.x;

            if(el[i].p1.y>maxY) maxY = el[i].p1.y;
            if(el[i].p2.y>maxY) maxY = el[i].p2.y;

            if(el[i].p1.x<minX) minX = el[i].p1.x;
            if(el[i].p2.x<minX) minX = el[i].p2.x;

            if(el[i].p1.y<minY) minY = el[i].p1.y;
            if(el[i].p2.y<minY) minY = el[i].p2.y;

            edgeList.push_back(i[el]);  // backward referencing
        }
    }
    void draw(){
        setcolor(color);
        for(Line l:edgeList) l.drawLine();
    }

    void vScanLineFill() const noexcept;
};

void Shape::vScanLineFill() const noexcept {
    std::vector<uint16_t> points;

    for(uint16_t i=minX; i<=maxX; i++){
        points.clear();
        for(Line l:edgeList){
            float ry = l.getY(i);

            if( true //ry >= minY && ry <= maxY     // if it is within range of shape (not necessary to check)
                    && ry >= l.minY && ry <= l.maxY  // if it is within range of line
            ) points.push_back(ry);
        }

        std::sort(points.begin(),points.end());  // sorting the points
        for(uint16_t j=0;j<points.size();j+=2){
            if(j<points.size()-1){
                setcolor(color);
                line(i,points[j],i,points[j+1]);
            }
        }
    }

    //shape enclosing
    /*line(minX,minY,maxX,minY);
    line(minX,maxY,maxX,maxY);
    line(minX,minY,minX,maxY);
    line(maxX,minY,maxX,maxY);*/
}

#endif //SHAPE