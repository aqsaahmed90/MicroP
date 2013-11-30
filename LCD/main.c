#include "main.h"
#include "hd44780_driver.h"
/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */



 int main (void) {
	
	AccelInit();
	LCD_init();
//#ifdef TEST		
//		if (((pitch + n) < -90) || ((pitch + n) >90))
//      n = -n; // if maximum/minimum change direction
//		
//		if (((roll + m) < -90) || ((roll + m) >  90))
//      m = -m; // if maximum/minimum change direction
//		
//		pitch = pitch + n;
//		roll  = pitch + m;
//#endif	
//	LCD_print_angle(-90,-90);
//	
//	char buffer [6];
//  double cx = -2.33445;
	double p = 24.543535642;
	double r = 34.2343445;
	char pitch [7];
	char roll  [7];

  //puts (buffer);
	LCD_clear_display();
//	osDelay(100);
//	LCD_write_char(buffer,5);
//	
//	cx = -3.23423545;
//	snprintf ( buffer, sizeof(buffer), "%f",cx);
//	LCD_write_char(buffer,5);
	while(1){
		
		//LCD_clear_display();
		snprintf ( pitch, sizeof(pitch), "%f",p);
		snprintf ( roll, sizeof(roll), "%f",r);

		LCD_print_angle(pitch,roll);
		
		p = p+0.5;
		r = r+0.5;
		
	}
	
	

  }


