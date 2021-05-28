#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP
#include "mbed.h"
#include "FIFO.h"

void data_emulator(int _tally, FIFO* _primary, FIFO* _secondry, Serial* _pc);
void send_data(FIFO* _primary, FIFO* _secondry, Serial* _pc, Serial* serial2);
int read_data(Serial* _pc, Serial* _serial2);

#endif