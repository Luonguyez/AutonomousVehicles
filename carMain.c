#include <sonar.h>


 
// LCD pins init.
//!#define LCD_ENABLE_PIN PIN_B6
//!#define LCD_RS_PIN PIN_B4
//!#define LCD_RW_PIN PIN_B5
//!#define LCD_DATA4 PIN_D4
//!#define LCD_DATA5 PIN_D5
//!#define LCD_DATA6 PIN_D6
//!#define LCD_DATA7 PIN_D7
 
#define trig PIN_D3
#define echo PIN_D4
//!#include <lcd.c>
  
float distance,time;
 
void main()
{
  setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
    set_tris_b(0xff);
    port_b_pullups(1);
  
    set_tris_d(0x00); // port D as output
  
  set_tris_c(0);
      setup_ccp1(CCP_PWM);
      setup_ccp2(CCP_PWM);
      setup_timer_2(T2_DIV_BY_16,249,1);
       delay_ms(100);
   
  output_high(PIN_D2); // something like starting whistle by buzzer for one sec
  delay_ms(1000);
  output_low(PIN_D2);
   output_low(PIN_C0);
      set_pwm1_duty(0);
       output_low(PIN_C3);  
      set_pwm2_duty(0);

   
  while(1)
  {
    output_high(trig);
    delay_us(10); // 10us pulse
    output_low(trig);
     
    while(input(echo)!=1); // until the echo pin become high
    set_timer1(0); // set timer to 0 for fresh count
    while(input(echo)!=0); // continue to the counting until echo pin become low
    time=get_timer1();
    distance=time*0.2/58.0f; // f = 4MHz/4 = 1MHz -> T = 1/1MHz = 1us.                                   f=20Mhz/4 = 5Mhz -> T = 0.2us 
          // speed of sound in air 340m/s = 34.000cm/1.000.000us = 0.034 cm/us                       340m/s = 34000cm/ =0.17cm/us
          // distance = speed * time = 0.034 * time                                                  0.17*time
          // actual distance = (0.034*time)/2 = 0.017*time (go to the target and return)             (0.17*time)/2 = 0.085*time 
    if(distance<20) // make some noise if distance lower than 5cms. 
      {             // (a kind of parking sensor)
      output_high(PIN_D2);
      
      setup_ccp1(CCP_off);
      setup_ccp2(ccp_off);
      
      output_low(PIN_C0);
      output_low(PIN_C1);
      output_low(PIN_C3);  
      output_low(PIN_C2);
      
      delay_ms(500);
      }
    else
    {
     setup_ccp1(CCP_pwm);
      setup_ccp2(ccp_pwm);
      set_pwm1_duty(100);   
      output_low(PIN_C0);
      set_pwm2_duty(100);
      output_low(PIN_C3);  
      }
//!     
//!    lcd_init();
//!    lcd_gotoxy(1,1);
//!    lcd_putc("\fDistance:");
//!    lcd_gotoxy(1,2);
//!    printf(LCD_PUTC,"%.2fcm",distance);
    delay_ms(500); // delay 0.5 sec for new measurement
    
    
  }
  }

 
