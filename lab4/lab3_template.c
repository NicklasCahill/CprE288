/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
#include "cyBot_FindObjects.h"                        // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1
#include "open_interface.h"

//#warning "Possible unimplemented functions"
#define REPLACEME 0
void moveForward(oi_t* sensor_data , double distance);
void turnRight(oi_t* sensor_data , int angle);
void turnLeft(oi_t* sensor_data , int angle);
void bumpLeft(oi_t* sensor_data);




int main(void) {
   resetSimulationBoard();


	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	            // Don't forget to initialize the cyBot UART before trying to use it
	cyBot_uart_init();
	oi_t *sensor_data = oi_alloc();// do this only once at start of main()
	oi_init(sensor_data);// do this only once at start of main()
	//int i;
	//turnRight(sensor_data,90);



	int n = 0;
	cyBot_Object_t ObjectList[3];
	cyBot_Object_t smallest;



	while(1)
	{
	    cyBot_FindObjects(ObjectList, 3);
	    smallest = ObjectList[0];
	    for(n = 0; n < 3; n++)
	    {
	        if(ObjectList[n].width > 1 && ObjectList[n].width < smallest.width)
	        {
	            smallest = ObjectList[n];
	        }
	    }
	    writePutty(ObjectList);

	    if(smallest.distance < 20)
        {
	        break;
        }
	    if(smallest.angle - 90 < 0)
	    {
	        turnLeft(sensor_data ,90 - (smallest.angle + 20));
	    }
	    else
	    {
	        turnRight(sensor_data , 90 - (smallest.angle - 90));
	    }


	    moveForward(sensor_data , 200.0);
	}
	moveForward(sensor_data , (smallest.distance*10) - 40);
	oi_free(sensor_data);


}

void writePutty(cyBot_Object_t ObjectList[])
{
    char buffer [35];
    int n,m,i;
    char names[50] = "Object    Angle   Distance    Width\n\r";
    for(i = 0; i < sizeof(names); i++)
         {
            cyBot_sendByte(names[i]);
         }

       for(n = 0; n < 3; n++)
            {
               sprintf(buffer, "%d   %d    %f   %f \n\r",n+1, ObjectList[n].angle, ObjectList[n].distance , ObjectList[n].width);


              for(m = 0; m < sizeof(buffer); m++){
                  cyBot_sendByte(buffer[m]);
              }
            }

}
void moveForward(oi_t* sensor_data , double distance)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(500,500); //move forward at full speed
        while(sum < distance)
        {
            oi_update(sensor_data);
            if(sensor_data -> bumpLeft)
             {
              bumpLeft(sensor_data);
              oi_setWheels(500,500);
              sum-=50;
             }
            else if(sensor_data -> bumpRight)
              {
              bumpRight(sensor_data);
              oi_setWheels(500,500);
              sum-=50;
              }
             sum += sensor_data -> distance; // use -> notation since pointer
        }
    oi_setWheels(0,0); //stop
     // do this once at end of main()}
}


void turnRight(oi_t* sensor_data , int angle)
{
    double sum = 0;
    oi_setWheels(100,-100);
    while(sum < angle)
           {
               oi_update(sensor_data);
                sum += sensor_data -> angle; // use -> notation since pointer
           }
    oi_setWheels(0,0);
}
void turnLeft(oi_t* sensor_data , int angle)
{
    double sum = 0;
    oi_setWheels(-100,100);
    while(sum < angle)
           {
               oi_update(sensor_data);

               sum -= sensor_data -> angle; // use -> notation since pointer
           }
    oi_setWheels(0,0);
}

void bumpLeft(oi_t* sensor_data)
{
    int sum = 0;
    oi_setWheels(-100,-100); //move forward at full speed
           while(sum > -50)
           {
               oi_update(sensor_data);
                sum += sensor_data -> distance; // use -> notation since pointer
           }
           oi_setWheels(0,0);
    turnRight(sensor_data , 90);
    moveForward(sensor_data ,150);
    turnLeft(sensor_data , 90);

}

void bumpRight(oi_t* sensor_data)
{
    int sum = 0;
    oi_setWheels(-100,-100); //move forward at full speed
           while(sum > -50)
           {
               oi_update(sensor_data);
                sum += sensor_data -> distance; // use -> notation since pointer
           }
           oi_setWheels(0,0);
    turnLeft(sensor_data , 90);
    moveForward(sensor_data ,150);
    turnRight(sensor_data , 90);

}

