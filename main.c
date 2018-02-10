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
    int radius = 10, x, y, midy,midx,i=0,flag=0;
    int xx=0,yy=0;
    int xa,ya,xb,yb;

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
        line(x, y + radius, x, y + radius + 40);

        /* leg design */
        line(x, y + radius + 40, x - 10, getmaxy() - 80);
        line(x, y + radius + 40, x + 10, getmaxy() - 80);
        
        /* hand design */
        line(x, y + radius + 10, x - 15, y + radius + 30);
        line(x, y + radius + 10, x + 15, y + radius + 30);
        
        /*image 2 - position of 2nd stickman*/
        circle(x+550,y,radius);
        line(x+550, y + radius,x + 550,y + radius + 40);
        
        /*leg design*/
        line(x+550,y+radius+40,x+540,getmaxy() - 80);
        line(x+550,y+radius+40,x+560,getmaxy() - 80);
        
        /*hand design*/
        line(x+550, y + radius + 10,x+ 535, y + radius + 30);
        line(x+550, y + radius + 10,x+565, y + radius + 30);

        /*net design*/
        line(midx,getmaxy() - 50, midx, midy+30);
        line(midx,midy+30,midx-50,midy-100);             
        line(midx-50,midy-100,midx-50,midy+50);
        line(midx,getmaxy()-100,midx-50,midy);
        line(0,midy+50,getmaxx(),midy+50);

        
        xa=x+50;
        ya=y+50;
        xb=getmaxx()-50;
        yb=getmaxy()-50;
       	while(1){
            if (_kbhit()) {
                int ch = _getch();
                _putch(ch);
               // printf("%c",ch);
                //for player1
                if (ch=='w') ya--;
                if (ch=='s') ya++;
                if (ch=='a') xa--;
                if (ch=='d') xa++;

                 /*switch (ch) {
                    case 'w':
                        xx=0;yy=1;
                        xa = xa + xx;
                        ya = ya - yy;
                        //circle(xa,ya,radius);
                    case 's':
                        xx=0;yy=1;
                        xa = xa + xx;
                        ya = ya + yy;
                        //circle(xa,ya,radius);
                    case 'a':
                        xx=1;yy=0;
                        xa = xa - xx;
                        ya = ya + yy;
                        //circle(xa,ya,radius);
                    case 'd':
                        xx=1;yy=0;
                        xa = xa + xx;
                        ya = ya + yy;
                       // circle(xa,ya,radius);
                }*/
                //for player2
                if (ch=='i') yb--;
                if (ch=='j') yb++;
                if (ch=='k') xb--;
                if (ch=='l') xb++;
            }

        while (xx<=getmaxx()){
            
            /*ball design*/
            circle(xx+50,yy+50,15);
            
            if (i % 10 == 0) {
                        /* left to right */
                        xx = xx + 5;
                        i = 0;
                    }
                     
            
            if(flag)
            {
                /*bottom to top*/
                yy=yy-10;

                }else{

                /*top to bottom*/
                yy=yy+10;

                }
            
                /* check whether ball reached y-axis maximum */
                if (yy >= getmaxy()) {
                        flag = 1;
                } else if (yy <= 0) {
                        flag = 0;
                }

                /* sleeps for 50 milliseconds */
                delay(50);
        
            i++;
         
       		}

            }
            
        }
    

    //getch();
    cleardevice();
    close_keyboard();

    /* deallocate memory allocated for graphic screen */
    delay(50);
    closegraph();

    return 0;
}
