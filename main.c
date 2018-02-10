#include <stdlib.h>
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

int main() 
{
    /* request auto detection */
    int gd = DETECT, gm, err;
    int radius = 10, x, y, midy,midx,i;
    int xx=0,yy=0;
    int xa,ya;

    /* initialize graphic mode */
    initgraph (&gd, &gm,NULL);
    x = 40;
    midx = getmaxx() /2;
    midy = getmaxy() / 2;
    y = midy + 100;

    init_keyboard();

    while (x < getmaxx() - 25) {
        /* clears graphic screen */
        cleardevice();

        setlinestyle(SOLID_LINE, 1, 3);
        /* road for stick man */
        line(0, getmaxy() - 50, getmaxx(),getmaxy() -50);

        /* image 1  -position of 1st stick man */
        circle(x, y, radius);
        line(x, y + radius, x, y + radius + 50);

        /* leg design */
        line(x, y + radius + 50, x - 10, getmaxy() - 50);
        line(x, y + radius + 50, x + 10, getmaxy() -50);
        
        /* hand design */
        line(x, y + radius + 10, x - 15, y + radius + 40);
        line(x, y + radius + 10, x + 15, y + radius + 40);
        
        /*image 2 - position of 2nd stickman*/
        circle(x+550,y,radius);
        line(x+550, y + radius,x + 550,y + radius + 50);
        
        /*leg design*/
        line(x+550,y+radius+50,x+540,getmaxy() - 50);
        line(x+550,y+radius+50,x+560,getmaxy() - 50);
        
        /*hand design*/
        line(x+550, y + radius + 10,x+ 535, y + radius + 40);
        line(x+550, y + radius + 10,x+565, y + radius + 40);

        for (i=0;i<10;i++){
        /*net design*/
        line(midx,getmaxy() - 50, midx, midy+30);
        line(midx,midy+30,midx-50,midy-100);             
        line(midx-50,midy-100,midx-50,midy+50);
        line(midx,getmaxy()-100,midx-50,midy);
        line(0,midy+50,getmaxx(),midy+50);}

        /*ball design*/
        xa=x+50;
        ya=y+50;
        while(1){
            circle(xa,ya,radius);
            if (_kbhit()) {
                int ch = _getch();
                _putch(ch);
                switch (ch) {
                    case 'w':
                        xx=0;yy=-1;
                        xa = xa + xx;
                        ya = ya + yy;
                    case 's':
                        xx=0;yy=1;
                        xa = xa + xx;
                        ya = ya + yy;
                    case 'a':
                        xx=-1;yy=0;
                        xa = xa + xx;
                        ya = ya + yy;
                    case 'd':
                        xx=1;yy-0;
                        xa = xa + xx;
                        ya = ya + yy;
                    default:
                        xx=0;yy=-1;
                        xa = xa + xx;
                        ya = ya + yy;
                }
            }

            delay(50);
        }
    }

    //getch();

    close_keyboard();

    /* deallocate memory allocated for graphic screen */
    delay(50);
    closegraph();

    return 0;
}
