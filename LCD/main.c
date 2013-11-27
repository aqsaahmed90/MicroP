#include "main.h"
#include "hd44780_driver.h"
/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */


 int main (void) {

   LCD_init();
   
	 //gpio_LCD_init();
	 
	/* Set the Enable pin high */
	GPIO_SetBits(GPIO_PORT_E, LCD_E);
	osDelay(100);
	 
   while(1) {
       LCD_clear_display();
       osDelay(1000);
       LCD_write_char("Please", 6);
       osDelay(1000);
       LCD_write_char(" Work",  5);
       osDelay(1000);
       LCD_move_second_line();
       LCD_write_char(" NOW!",  5);
       osDelay(5000);
    }
  }
