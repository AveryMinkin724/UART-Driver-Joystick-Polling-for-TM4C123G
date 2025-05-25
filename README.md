# UART Driver Joystick Polling for TM4C123G

GPIO Pins Used:

  For Joystick:
  PE1: SW - digital  
  PE2: Vy - analog  
  PE3: Vx - analog  
  
  For UART:
  PE4: RX on TM4C  
  PE5: TX on TM4C

Putty Terminal: COM4, 115200 baud rate, serial, telnet

Keil MDK Project: UART_Driver

This program uses adc polling on TM4C GPIO pins to poll the X & Y readings from a the joystick connected to the pins above. The SW input is not being polled but the sequenc sampler can be configured to pole that as well. These values are then read and sent out by the uart driver (driving a USB to TTL device) to a putty terminal. The scaling seems off and could be tuned. 
