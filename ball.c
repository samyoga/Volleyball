        while (xx<=getmaxx()){
            
            /*ball design*/
            circle(xx+50,yy+50,5);
            
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