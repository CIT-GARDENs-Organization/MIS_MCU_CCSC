#INT_TIMER0
static void TIMER0_isr(void)
{
   // every 0.01 sec interrupts
   set_timer0(100);

   if (++subsec >= 100)
   {
      subsec = 0;
      sec++;

      if (sec >= SEC_IN_A_DAY)
      {
         sec -= SEC_IN_A_DAY;
         day++;
      }
   }
}

void setup_timer()
{
   setup_timer_0(T0_INTERNAL | T0_DIV_256 | RTCC_8_BIT);
   enable_interrupts(INT_TIMER0);
}
