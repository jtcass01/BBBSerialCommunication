/*
 * control.h
 *
 *  Created on: Nov 25, 2012
 *  Author: Jaz Stanberry
 */

#ifndef CONTROL_H_
#define CONTROL_H_

int uartInit(void);
int sendXbee(const char*);
int readXbee();

#endif /* CONTROL_H_ */