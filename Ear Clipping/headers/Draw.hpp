#include "Shape.hpp"
#include <graphics.h>
#include <vector>
#include <tuple>

// Stores the list of all triangles
std::vector<std::tuple<int16_t,int16_t>> triangles;

void floodFill(int a,int b,int fillColor, int boundaryColor){
    int c=getpixel(a,b);
    if(c==fillColor || c==boundaryColor) return;

    putpixel(a,b,fillColor);
    floodFill(a,b+1,fillColor,boundaryColor);
    floodFill(a,b-1,fillColor,boundaryColor);
    floodFill(a+1,b,fillColor,boundaryColor);
    floodFill(a-1,b,fillColor,boundaryColor);
}

void scaleShape(Point& p,int16_t scaleFactorX,int16_t scaleFactorY,uint16_t n){
    Point* p1 = &p;
    for(int i=0;i<n;i++){
        p1->x = p1->x*scaleFactorX;
        p1->y = p1->y*scaleFactorY;
        p1 = p1->next;
    }
}

std::vector<Point*> getPointArr(Point& p){
    std::vector<Point*> points;

    // Initialize the set of points
    int16_t startX = p.x; 
    int16_t startY = p.y;
    Point* p1 = p.next;

    while(p1->x != startX || p1->y != startY){
        points.push_back(p1);
        p1 = p1->next;
    }
    points.push_back(p1);
    return points;
}

void triangulate(Point& p){
    auto points = getPointArr(p);
    
    while(points.size()>3){
        std::vector<Point*>::iterator it = points.begin();
        
        for(;it!=points.end();it++){
            
            // TODO: Check if the given vertex is a ear node
            Vectors v1 = Vectors((*it)->prev->x - (*it)->x , (*it)->prev->y - (*it)->y);  // v1 = b-a
            Vectors v2 = Vectors((*it)->next->x - (*it)->x , (*it)->next->y - (*it)->y);  // v2 = c-a

            _Float32 cross = v1.cross(v2);
            bool isValidEar = cross>0;

            if(isValidEar){   
                // circle((*it)->x+xOffSet,(*it)->y+yOffSet,10);
                v1.constMul(-1.0);  // v1 = a-b
                v2.constMul(-1.0);  // v2 = a-c
                Vectors v3 = Vectors((*it)->next->x - (*it)->prev->x , (*it)->next->y - (*it)->prev->y); // v3 = c-b

                for(Point* p:points){
                    bool isVertex = ((*p) == (*(*it))) || ((*p) == (*(*it)->next)) || ((*p) == (*(*it)->prev));
                    if(!isVertex){
                        Vectors ap = (*p)-(*(*it));
                        Vectors bp = (*p)-(*(*it)->prev);
                        Vectors cp = (*p)-(*(*it)->next);
                        
                        _Float32 cross1 = v1.cross(ap);
                        _Float32 cross2 = v2.cross(cp);
                        _Float32 cross3 = v3.cross(bp);

                        isValidEar = (cross1<=0 && cross2<=0 && cross3<=0);
                        if(isValidEar) break;
                    }
                }
            } // If it is less than 0 then it is a reflex angle so we move on to the next vertex

            if(isValidEar){
                line((*it)->prev->x+xOffSet,(*it)->prev->y+yOffSet,(*it)->next->x+xOffSet,(*it)->next->y+yOffSet);

                _Float32 x = (*it)->x + (*it)->next->x + (*it)->prev->x;
                _Float32 y = (*it)->y + (*it)->next->y + (*it)->prev->y;
                x /= 3.0; y /= 3.0;
                std::tuple<int16_t,int16_t> tp = std::make_tuple((int16_t)x,(int16_t)y);
                triangles.push_back(tp);

                (*it)->prev->next = (*it)->next;
                (*it)->next->prev = (*it)->prev;

                points = getPointArr(*(*it)->prev);
                
                (*it)->next = nullptr;
                (*it)->prev = nullptr;
                break;
            }   
        }
    }

    // At the end there is still 1 triangle left
    std::vector<Point*>::iterator it = points.begin();
    _Float32 x = (*it)->x + (*it)->next->x + (*it)->prev->x;
    _Float32 y = (*it)->y + (*it)->next->y + (*it)->prev->y;
    x /= 3.0; y /= 3.0;
    std::tuple<int16_t,int16_t> tp = std::make_tuple((int16_t)x,(int16_t)y);
    triangles.push_back(tp);
    
    // End of Function
}

void drawShape(Point& p,int color){
    int16_t x = p.x;
    int16_t y = p.y;

    int16_t n = 0;
    Point* p1 = &p;

    int colors[5] = {RED, GREEN, BLUE, YELLOW, CYAN};

    while(true){
        line(p1->x+xOffSet,p1->y+yOffSet,p1->next->x+xOffSet,p1->next->y+yOffSet);
        p1 = p1->next;
        if(p1->x == x && p1->y == y) break;
    }
    triangulate(p);
    for(int16_t i=0;i<triangles.size();i++){
        int16_t x = std::get<0>(triangles[i])+xOffSet;
        int16_t y = std::get<1>(triangles[i])+yOffSet;
        floodFill(x,y,colors[i%5],WHITE);
    }
}