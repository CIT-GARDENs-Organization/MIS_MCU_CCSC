#ifndef CONFIG_H
#define CONFIG_H

#device ADC=12

#FUSES NOWDT                    //No Watch Dog Timer

#use delay(crystal=16MHz, clock=16MHz)

#pin_select U1TX = PIN_F7
#pin_select U1RX = PIN_F5

#use rs232(baud=9600,parity=N,xmit=PIN_F7,rcv=PIN_F5,bits=8,stream=BOSS)

#pin_select U2TX = PIN_D3
#pin_select U2RX = PIN_D2

#use rs232(baud=9600,parity=N,xmit=PIN_D3,rcv=PIN_D2,bits=8,stream=PC)

#pin_select U3TX = PIN_E5
#pin_select U3RX = PIN_E4

#use rs232(baud=9600,parity=N,xmit=PIN_E5,rcv=PIN_E4,bits=8,stream=PORT3)

#pin_select U4TX = PIN_E3
#pin_select U4RX = PIN_F2

#use rs232(baud=9600,parity=N,xmit=PIN_E3,rcv=PIN_F2,bits=8,stream=PORT4)
#endif
