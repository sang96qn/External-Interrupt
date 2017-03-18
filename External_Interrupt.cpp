#include <msp430g2553.h>
#define LED_RED BIT0
#define LED_BLUE BIT6
#define BUTTON BIT3
void delay(int num);
#pragma vector = PORT1_VECTOR
__interrupt void ngat_ngoai(void)
{
  while(!(P1IN & BUTTON)); // wait for button release
  P1OUT ^= LED_RED;
  P1IFG &=~ BUTTON; // delete interrupt flag
}

int main()
{
  WDTCTL = WDTPW + WDTHOLD; // Stop Watchdog timer
  P1DIR |= LED_RED+LED_BLUE; // output
  P1DIR &=~ BUTTON; // input
  P1REN |= BUTTON; //enable pull resistor
  P1OUT |= BUTTON; // pull up resistor
  P1IE |= BUTTON; // interrupt enable
  P1IES |= BUTTON;
  _BIS_SR(LPM0_bits+GIE); // global interrupt -> CPUOFF 

}
void delay(int num)
{
  for(int i=0;i<=num;i++)
  __delay_cycles(1000);
}
