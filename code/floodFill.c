// C code to illustrate using
// graphics in linux environment
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

void midPointCircle(int a,int b,int r,int color){
    int x=0, y=r, p=1-r;
    do{
        putpixel(a+x,b+y,color);
        putpixel(a+y,b+x,color);
        putpixel(a-y,b+x,color);
        putpixel(a-x,b+y,color);
        putpixel(a-x,b-y,color);
        putpixel(a-y,b-x,color);
        putpixel(a+y,b-x,color);
        putpixel(a+x,b-y,color);

        int y0=y;
        if(p<0) y=y0;
        else y=y0-1;
        int y1=(2*y0-1)/2;
        int y2=(2*y-1)/2;
        p=p+2*x+3-y1*y1+y2*y2;
        x++;
    }while(x<y);
}

void floodFill(int a,int b,int fillColor, int boundaryColor){
    int c=getpixel(a,b);
    if(c==fillColor || c==boundaryColor) return;

    putpixel(a,b,fillColor);
    floodFill(a,b+1,fillColor,boundaryColor);
    floodFill(a,b-1,fillColor,boundaryColor);
    floodFill(a+1,b,fillColor,boundaryColor);
    floodFill(a-1,b,fillColor,boundaryColor);
}

int main()
{
	int gd = VGA, gm=VGAMAX;
	initgraph(&gd, &gm, NULL);

	midPointCircle(150, 150, 70, RED);
	midPointCircle(300, 150, 70, GREEN);
	midPointCircle(150, 300, 70, YELLOW);
	midPointCircle(300, 300, 70, LIGHTBLUE);

	floodFill(150,150,RED,RED);
	floodFill(300,150,GREEN,GREEN);
	floodFill(150, 300,YELLOW,YELLOW);
	floodFill(300, 300,LIGHTBLUE,LIGHTBLUE);

	getch();
	closegraph();
	return 0;
}
