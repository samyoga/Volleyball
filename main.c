
 #include <graphics.h>

  int main() 
  {
        /* request auto detection */
        int gd = DETECT, gm, err;
        int radius = 10, x, y, midy;

        /* initialize graphic mode */
        initgraph (&gd, &gm,NULL);
      /*  err = graphresult(); */

       /* if (err != grOk) {
                /* error occurred */
              /*  printf("Graphics Error: %s\n",
                                grapherrormsg(err));
                return 0;
        } */

        x = 50;
        midy = getmaxy() / 2;
        y = midy + 100;

        /*
         * used 5 stick man (still/image)
         * position to get walking animation
         */
        while (x < getmaxx() - 25) {
                /* clears graphic screen */
                cleardevice();

                setlinestyle(SOLID_LINE, 1, 3);
                /* road for stick man */
                line(0, getmaxy() - 50, getmaxx(),getmaxy() -50);

                /* image 1  - first position of 1st stick man */
                circle(x, y, radius);
                line(x, y + radius, x, y + radius + 50);

                /* leg design */
                line(x, y + radius + 50, x - 10, getmaxy() - 50);
                line(x, y + radius + 50, x + 10, getmaxy() -50);
              
                /* hand motion */
                line(x, y + radius + 10, x - 15, y + radius + 40);
                line(x, y + radius + 10, x + 15, y + radius + 40);
                
               /*image 2 - position of 2nd stickman*/
                circle(x+450,y,radius);
                line(x+450, y + radius, x+450, y + radius + 50);
                
                /*leg design*/
                line(x+450,y+radius+50,x+440,getmaxy() - 50);
                line(x+450,y+radius+50,x+460,getmaxy() - 50);
                
                /*hand design*/
                line(x+450, y + radius + 10, x + 435, y + radius + 40);
                line(x+450, y + radius + 10, x + 465, y + radius + 40);


        }

        getch();

        /* deallocate memory allocated for graphic screen */
        delay(50);
        closegraph();

        return 0;
  }
