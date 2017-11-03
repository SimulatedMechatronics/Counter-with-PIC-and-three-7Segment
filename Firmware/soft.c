#include "soft.h"
int const seg[] = {
0b00111111,
0b00000110,
0b01011011,
0b01001111,
0b01100110,
0b01101101,
0b01111101,
0b00000111,
0b01111111,
0b01101111
};
int cen=1;
int dez=8;
int uni=0;
int num=0;
int dig=0;
#int_TIMER0
void  TIMER0_isr(void) {
   dig++;
   if(dig>2) dig=0;
   switch(dig) {
      case 0:
         num=uni;
         output_a(1);
         break;
      case 1:
         num=dez;
         output_a(2);
         break;
      case 2:
         num=cen;
         output_a(4);
   }
   output_b(seg[num]);
   clear_interrupt(INT_TIMER0);
}



void main() {
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   while(true) {
      uni++;
      if(uni>9) {
         uni=0;
         dez++;
      }
      if(dez>9) {
         dez=0;
         cen++;
      }
      if(cen>9) {
         cen=0;
         dez=0;
         uni=0;
      }
      delay_ms(250);
   }
}
