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
    int radius = 10, x, y, midy,midx,i=0,flag=0,a;
    int xx=0,yy=0;



    int xa,ya,xb,yb;

    /* initialize graphic mode */
    initgraph (&gd, &gm,NULL);
    x = 40;
    midx = getmaxx() /2;
    midy = getmaxy() / 2;
    y = midy + 100;
    xa=x;
    ya=y;
    xb=x;
    yb=y;
    init_keyboard();

    while (x < getmaxx() - 25) {
        /* clears graphic screen */
        cleardevice();

        xa=x+50;
        ya=y+50;
        xb=getmaxx()-50;
        yb=getmaxy()-50;
         label:
       	while(1){
            setlinestyle(SOLID_LINE, 1, 3);
            /* road for stick man */
            line(0, getmaxy() - 50, getmaxx(),getmaxy() -50);

            /*net design*/
            line(midx,getmaxy() - 50, midx, midy+30);
            line(midx,midy+30,midx-50,midy-100);             
            line(midx-50,midy-100,midx-50,midy+50);
            line(midx,getmaxy()-100,midx-50,midy);
            line(0,midy+50,getmaxx(),midy+50);
            /* image 1  -position of 1st stick man */
            circle(xa-30, ya-50, radius);
            line(xa-30, ya + radius-50, xa-30, ya + radius - 10);

            /* leg design */
            line(xa-30, ya + radius - 10, xa - 20, ya +radius +10);
            line(xa-30, ya + radius - 10, xa - 40, ya +radius +10);
            
            /* hand design */
            line(xa-30, ya + radius -40, xa - 15, ya + radius -20 );
            line(xa-30, ya + radius -40, xa -45, ya + radius -20 );

            /*image 2 - position of 2nd stickman*/
            circle(xb,yb-90,radius);
            line(xb, yb + radius-90,xb,yb + radius -60);
            
            /*leg design*/
            line(xb,yb+radius-60,xb-10,yb+ radius -40);
            line(xb,yb+radius-60,xb+10,yb +radius -40);
            
            /*hand design*/
            line(xb, yb + radius - 80,xb-15, yb + radius - 60);
            line(xb, yb + radius - 80,xb+15, yb + radius - 60);
            
            /*ball design*/
           
            circle(xx+60,yy+50,7);
            	/*delay(50);
            	cleardevice();
            	if (flag==0){
            		yy==yy-1;
            	}
            	else if(flag ==1) {yy=yy+1;
            	if ((yy+57)==(ya-50-radius))
            	{
            		yy=yy-200;
            		xx=xx+300;
            		delay(50);
            	}
            	else {goto label;}
            }

            if (yy>=getmaxy()-100){
            		flag=1;
            	}
            	else if (yy<=0){
            		flag=0;
            	}

            	if (i){
            			delay(100);
            			cleardevice();
            		
            			xx=xx+1; 
           
            	if ((yy+57)==(yb-90-radius)||(xx+67)==xb-radius){
            		yy=yy-200;
            		xx=xx-300;

            	}
            

            	if (xx>=getmaxx()-100){
            		i=1;
            	}
            	else if(xx<=0){
            		i=0;
            	}
            	}*/
            

            

           
            
            if(flag){
             /*bottom to top*/
                yy=yy-1;}
			else{
                /*top to bottom*/
                yy=yy+1;
                if ((yy+57)==(ya-50-radius)){
                	yy=yy-300;
                	a=yy;
            		xx=xx+530;
            		}
            		
            	}
            if ((yy-236)==(yb-90-radius)){

            	yy=yy-300;
            	xx=xx-530;
            }
              
            /* check whether ball reached y-axis maximum */
           // if (((yy+57)==(ya-50-radius))||(yy+57)==(yb-90-radius)){
            if (yy>=getmaxy()-100) { 
                    flag = 1;
            } 
            else if (yy <= 0) {
                    flag = 0;
            }

          /*  if (i){
            	/*right to left*/
            	/*xx=xx-50;          
            }
            else{
            	/*left to right*/
            	/*xx=xx+50;


            }

           // if (((xx+67)==(xa-30-radius))||(xx+getmaxx()-50)==(xb)){
            if(xx >=getmaxx()-100){
            	i=1;
            }
            else if (xx<=0){
            	i=0;
            }
        
        

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
