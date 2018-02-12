#include <stdio.h>
//#include <conio.h>
//#include <graphics.h>
//#include <dos.h>
#include <math.h>
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

/* manipulates the position of planets on the orbit */

void planetMotion(int xrad, int yrad, int midx, int midy, int x[8], int y[8]) {
        int i, j = 0;

        /* positions of planets in their corresponding orbits */
        for (i = 180; i > 0; i = i - 6) {
                x[j] = midx - (xrad * cos((i * 3.14) / 180));
                y[j++] = midy - (yrad * sin((i * 3.14) / 180));
                //printf ("%d, %d" , x[j],y[j]);
                //outtextxy(200, 425, "C Graphics Program");
        }
        return;
}

int main() {
        /* request auto detection */
        int gdriver = DETECT, gmode, err;
        int i = 0, midx, midy;
        int xrad, yrad, x[9][60], y[9][60];
        int radius, tmp;
        int posn;
        /* initialize graphic mode */
        initgraph(&gdriver, &gmode, NULL);

        /* mid positions at x and y-axis */
        midx = getmaxx() / 2;
        midy = getmaxy() / 2;

        /* manipulating radius of all 9 planets */
        radius = 10;
        
        posn = 48;

        /* orbits for all 9 planets */

        xrad =  210;
        yrad =  105;

        /* positions of planets on their corresponding orbits */

        planetMotion(xrad, yrad, midx, midy, x[8], y[8]);

        init_keyboard();

        while (!_kbhit()) {
                /* drawing 9 orbits */
                setcolor(WHITE);
                
                ellipse(midx, midy, 0, 360, xrad, yrad);

                /* pluto in ninth orbit */
                setcolor(LIGHTRED);
                //setfillstyle(SOLID_FILL, LIGHTRED);
                pieslice(x[8][posn], y[8][posn], 0, 360, radius);

                /* checking for one complete rotation */

                if (posn <= 0) {
                        posn = 30;
                } else {
                        posn = posn - 1;
                }

                /* sleep for 100 milliseconds */
                delay(100);

                /* clears graphic screen */
                cleardevice();
        }

        close_keyboard();

        /* deallocate memory allocated for graphic screen */
        closegraph();
        return 0;
}
