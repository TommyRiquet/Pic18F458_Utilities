#include <main.h>

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
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(False);
    
   set_timer1(0);
   
   while(TRUE)
   {
   
  output_high(PIN_C1);
  delay_us(20);
  output_low(PIN_C1);
  
  while(!input(PIN_C0))
  {}
  
  set_timer1(0);
  
  while(input(PIN_C0))
  {}
  
  time = get_timer1();
  distance = time*0.028;
  delay_ms(500);
  
  // Gestion des LEDs rouge et verte
  if(distance < limit_distance){ 
     output_high(PIN_E0);
     output_low(PIN_E1);
     printf('Good')
  }else{
     output_toggle(PIN_E1);
     output_low(PIN_E0);
     printf('Alerte')
  }
  
  //Gestion des afficheurs
  if(distance < 100){
     output_low(PIN_E2);
     
     dizaine = distance /10;
     unite = distance - (dizaine*10);
     output_b((dizaine<<4)+unite);
  }else{
      output_high(PIN_E2);
      
      dizaine = distance / 100;
      unite = (distance - (dizaine*100))/10;
      output_b((dizaine<<4)+unite);
  }
  
}
}
