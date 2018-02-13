#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <graphics.h>

static struct termios initial_settings, new_settings;
 
static int peek_character = -1;
 
void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}
 
void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}
 
int _kbhit()
{
    unsigned char ch;
    int nread;
 
    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}
 
int _getch()
{
    char ch;
 
    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
 
int _putch(int c) {
    putchar(c);
    fflush(stdout);
    return c;
}

/* manipulates the position of planets on the orbit */

void Motion(int xrad, int yrad, int midx, int midy, int x[1], int y[1]) {
        int i, j = 0;

        /* positions of ball in ellipse*/
        for (i = 180; i > 0; i = i - 6) {
                x[j] = midx - (xrad * cos((i * 3.14) / 180));
                y[j++] = midy - (yrad * sin((i * 3.14) / 180));

        }
        return;
}

void AntiMotion(int xrad, int yrad, int midx, int midy, int x[1], int y[1]) {
        int i, j = 0;

        /* positions of ball in ellipse*/
        for (i = 290; i > 0; i = i - 6) {
                x[j] = midx + (xrad * sin((i * 3.14) / 180));
                y[j++] = midy + (yrad * cos((i * 3.14) / 180));

        }
        return;
}

int main() 
{
    /* request auto detection */
    int gd = DETECT, gm, err;
    int radius=10; 
    int x, y, midy,midx;
    int i=0;
    int xx=0,yy=0;
    int xrad, yrad, a[9][60], b[9][60];
    int tmp;
    int posn=20;

    int xa,ya,xb,yb;

    /* initialize graphic mode */
    initgraph (&gd, &gm,NULL);
    x = 40;
    y = midy+100;
    /*mid positions at x and y*/
    midx = getmaxx() /2;
    midy = getmaxy() / 2;

    xrad=290;
    yrad=200;

    
    xa=x;
    ya=y;
    xb=x;
    yb=y;

    /* positions of ball on corresponding ellipse */

        Motion(xrad-10, yrad, midx, midy+40, a[8], b[8]);

    init_keyboard();

    while (x < getmaxx() - 25) {
        /* clears graphic screen */
        cleardevice();

        xa=x+30;
        ya=getmaxy()-100;
        xb=getmaxx()-50;
        yb=getmaxy()-50;
         

       	while(1){
            setlinestyle(SOLID_LINE, 1, 3);
            /* road for stick man */
            line(0, getmaxy() - 50, getmaxx(),getmaxy() -50);

            /*net design*/
            line(midx,getmaxy() - 50, midx, midy+10);
            line(midx,midy+10,midx-60,midy-100);             
            line(midx-60,midy-100,midx-60,midy);
            line(midx,getmaxy()-120,midx-60,midy-20);
            line(0,midy,getmaxx(),midy);

            /* image 1  -position of 1st stick man */
            circle(xa-30, ya-100, radius);
            line(xa-30, ya + radius-100, xa-30, ya + radius - 70);

            /* leg design */
            line(xa-30, ya + radius - 70, xa - 20, ya +radius -50);
            line(xa-30, ya + radius - 70, xa - 40, ya +radius -50);
            
            /* hand design */
            line(xa-30, ya + radius -90, xa - 15, ya + radius -80 );
            line(xa-30, ya + radius -90, xa -45, ya + radius -80 );

            /*image 2 - position of 2nd stickman*/
            circle(xb,yb-150,radius);
            line(xb, yb + radius-150,xb,yb + radius -120);
            
            /*leg design*/
            line(xb,yb+radius-120,xb-10,yb+ radius -100);
            line(xb,yb+radius-120,xb+10,yb +radius -100);
            
            /*hand design*/
            line(xb, yb + radius - 140,xb-15, yb + radius - 130);
            line(xb, yb + radius - 140,xb+15, yb + radius - 130);
            
            /*ball design*/
           
                /* drawing orbits */
                setcolor(WHITE);
                
                ellipse(midx, midy+40, 0, 360, xrad, yrad);

                /* ball */
               setcolor(WHITE);
                //setfillstyle(SOLID_FILL, LIGHTRED);
                pieslice(a[8][posn], b[8][posn], 0, 360, radius);

                /* Motion(xrad, yrad, midx, midy, a[8], b[8]);
                if (((a[8][posn]+radius)==(xa-30+radius))&&((b[8][posn]+radius)==(ya-50+radius))){
                /* checking for one complete rotation */
                
                if (posn>0){
                    posn = posn - 1;
                    Motion(xrad, yrad, midx, midy+40, a[8], b[8]);
                }
            
               if (posn <= 0) {
                        while(posn!=30){
                            AntiMotion(xrad, yrad, midx, midy+40, a[8], b[8]);
                            posn = posn + 1;
                        }
                }
            

                /* sleep for 100 milliseconds */
                delay(100);

            
            /* sleeps for 50 milliseconds */
            delay(50);

            if (_kbhit()) {

                int ch = _getch();
                _putch(ch);
               // printf("%c",ch);
                //for player1
                if (ch=='w') ya--;
                if (ch=='s') ya++;
                if (ch=='a') xa--;
                if (ch=='d') xa++;

                //for player2
                if (ch=='i') yb--;
                if (ch=='k') yb++;
                if (ch=='j') xb--;
                if (ch=='l') xb++;
            }
            cleardevice();
        }
        delay(50);
    }

    //getch();
    close_keyboard();

    /* deallocate memory allocated for graphic screen */
    delay(50);
    closegraph();

    return 0;
}
