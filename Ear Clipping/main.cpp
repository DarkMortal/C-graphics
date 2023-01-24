#include "Draw.hpp"

int main(){
    int gd = VGA, gm=VGAMAX;
	initgraph(&gd, &gm, NULL);

    // A shape can be defined as a circular linked list
    Point a(-5,0),
    b(0,-3),
    c(0,0),
    d(5,-2),
    e(5,-6),
    f(0,-5),
    g(-5,-6);

    // forward connection
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = &g;
    g.next = &a;

    // backward connection
    g.prev = &f;
    f.prev = &e;
    e.prev = &d;
    d.prev = &c;
    c.prev = &b;
    b.prev = &a;
    a.prev = &g;

    scaleShape(a,30,25,7);
    drawShape(a,BLUE);

    getch();
	closegraph();
	return 0;
}