// C code to illustrate using
// graphics in linux environment
#include <stdio.h>
#include "Shape.hpp"

#define offsetX 100

int main()
{
	int gd = VGA, gm=VGAMAX;
	initgraph(&gd, &gm, NULL);

    Line lineArr1[] = {
        Line(Point(150+offsetX,150),Point(200+offsetX,250)),
        Line(Point(200+offsetX,250),Point(300+offsetX,150)),
        Line(Point(300+offsetX,150),Point(150+offsetX,150)),
    };
	Shape s1(lineArr1,sizeof(lineArr1)/sizeof(Line),BLUE);
    s1.draw();   
    s1.vScanLineFill();
    
    Line lineArr2[] = {
        Line(Point(50+offsetX,300),Point(150+offsetX,150)),
        Line(Point(150+offsetX,150),Point(200+offsetX,250)),
        Line(Point(200+offsetX,250),Point(300+offsetX,150)),
        Line(Point(300+offsetX,150),Point(350+offsetX,300)),
        Line(Point(350+offsetX,300),Point(50+offsetX,300)),
    };
    Shape s2(lineArr2,sizeof(lineArr2)/sizeof(Line),GREEN);
    s2.draw();
    s2.vScanLineFill();

    Line lineArr3[] = {
        Line(Point(3*35,4*35),Point(0,8*35)),
        Line(Point(0,8*35),Point(5*35,350)),
        Line(Point(5*35,350),Point(70,7*35)),
        Line(Point(70,7*35),Point(3*35,4*35)),
    };
    Shape s3(lineArr3,sizeof(lineArr3)/sizeof(Line),YELLOW);
    s3.draw();
    s3.vScanLineFill();

	getch();
	closegraph();
	return 0;
}