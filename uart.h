#ifndef UART_H
#define UART_H

void uart_init(void);
void Tiva_UART5_Transmitter_polling(char c);
char Tiva_UART5_Receiver_polling(void);
void UART5_check_connection(char *str);

#endif //UART_H
