#include <main.h>
#include <stdio.h>
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, ERRORS)

int16 dizaine,unite;
int16 limit_distance = 100;
int16 distance,time;


void main()
{
   
   setup_low_volt_detect(FALSE);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);      //104 ms overflow
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(False);
    
   set_timer1(0);
   
   while(TRUE)
   {
        //////////////////////////////
        //          DATA            //
        //////////////////////////////
        
  output_high(PIN_C0);
  delay_us(30);
  output_low(PIN_C0);
  
  while(!input(PIN_C1)){}
  set_timer1(0);
  while(input(PIN_C1)){}
  
  
  time = get_timer1();
  distance = time*0.025;
  
  
  delay_ms(500);
  
        //////////////////////////////
        //          LEDS            //
        //////////////////////////////
        
  if(distance < limit_distance){ 
     output_high(PIN_E1);
     output_low(PIN_E0);
     
  }else{
     output_toggle(PIN_E0);
     output_low(PIN_E1);
  }
  printf("%ld\n",distance);
 
  
        //////////////////////////////
        //      AFFICHEURS 7Seg     //
        //////////////////////////////
        
  if(distance < 100){
     output_low(PIN_E2);
     distance = distance ;
     dizaine = distance /10;
     unite = distance - (dizaine*10);
     output_b((dizaine<<4)+unite);
  }else{
      output_high(PIN_E2);
      
      dizaine = distance / 100;
      unite = (distance - (dizaine*100))/10;
      
  }
  
}
   }
//////////////////////////////////////////////////
//                ||                            //
//    PIN C0      ||    Pin Trigger de la sonde //
//    PIN C1      ||    Pin Echo de la sonde    //
//    PIN E0      ||    Led Verte               //
//    PIN E1      ||    Led Rouge               //
//    PIN E2      ||    Point des afficheurs    //
//    PIN B0-7    ||    8 Pins des afficheurs   //
//                ||                            //
//////////////////////////////////////////////////
