//============================================================================
// File        : control.cpp
// Author      : Jaz Stanberry
// Copyright   : 2012
// Description : Enables UART communication in the BeagleBone using UARTs 2 and 4.
//               It also enables UARTs 1,2,4,5.
//============================================================================

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <termios.h>    /*Enables us to set baud rate for RX/TX separately*/
#include <fcntl.h>      /*Enables use of flags to modify open(), read(), write() functions*/
#include <unistd.h>     /*Enables use of open(), read(), write()*/
#include "uart.h"
#include "control.h"
using namespace std;

int main(void) {
	uartInit();
	readXbee(); //The receiving (RX) pin is connected to TTY02
	sendXbee("Test"); //The transmitting (TX) pin is connected to TTY04
}

int readXbee(void) {
	int ARRAY_SIZE = 5; //We're assuming that the XBee is going to send 5 bytes. Change it as you see fit.
	termios Xbee;
	char byte_in[5];
	int* fd, bytes_read;
	if ((fd = open("/dev/ttyO2", O_RDWR | O_NOCTTY)) < 0) {
		cout << "Could not open port." << endl;
		return -1;
	}
	if (tcgetattr(fd, &Xbee) != 0) { /* Obtain current terminal device settings in order to modify them at a later time. */
		cout << "Unable to retrieve port attributes." << endl;
		return -1;
	}
	if (cfsetispeed(&Xbee, B9600) < 0) { /* Sets baud rate to 9600 */
		cout << "Input baud rate not successfully set." << endl;
	}
	Xbee.c_iflag = 0;
	Xbee.c_oflag = 0;
	Xbee.c_lflag = 0;
	Xbee.c_cc[VMIN] = ARRAY_SIZE; /* Wait for an array of a certain size to enter the buffer before moving on. */
	Xbee.c_cc[VTIME] = 1;/* Timeout after 0.1 seconds */
	tcsetattr(fd, TCSANOW, &Xbee); /* Set newly-modified attributes. */
	bytes_read = read(fd, byte_in, ARRAY_SIZE); /* Reads ttyO port, stores data into byte_in. */

	for (int i = ARRAY_SIZE; i < ARRAY_SIZE; i++) {
		cout << bytes_read[i] << endl;
	}
	close(fd);
	return 1;
}

int sendXbee(const char *msg) { /* Pass some string into this function to be sent out. */
	termios Xbee;
	int size = strlen(msg); /* Obtain the size of the string; for use in write() */
	int fd;
	if ((fd = open("/dev/ttyO4", O_RDWR | O_NOCTTY)) < 0) {
		cout << "Could not open ttyO4." << endl;
		return -1;
	}
	if (cfsetospeed(&Xbee, B9600) < 0) {
		cout << "Input baud rate not successfully set." << endl;
	}
	if (tcgetattr(fd, &Xbee) != 0) { /* Obtain current terminal device settings in order to modify them at a later time. */
		cout << "Unable to retrieve port attributes." << endl;
		return -1;
	}
	Xbee.c_iflag = 0;
	Xbee.c_oflag = 0;
	Xbee.c_lflag = 0;
	Xbee.c_cc[VMIN] = 0;
	Xbee.c_cc[VTIME] = 1; //Timeout after 0.1 seconds.
	tcsetattr(fd, TCSANOW, &Xbee); //Set newly-modified attributes
	write(fd, msg, size);
	close(fd);
	return 1;
}

/* Initialize UARTs 1, 2, 4, 5 */
int uartInit(void) {
	cout << "Initializing UARTs. " << endl;
	char    tx1ModeSet[4], rx1ModeSet[4], tx2ModeSet[4], rx2ModeSet[4], tx4ModeSet[4], rx4ModeSet[4], tx5ModeSet[4], rx5ModeSet[4],
            tx1Mode[4], rx1Mode[4], tx2Mode[4], rx2Mode[4], tx4Mode[4], rx4Mode[4], tx5Mode[4], rx5Mode[4];

	sprintf(tx1Mode, "%d", 0);
	sprintf(rx1Mode, "%d", 20);
	sprintf(tx2Mode, "%d", 1);
	sprintf(rx2Mode, "%d", 21);
	sprintf(tx4Mode, "%d", 6);
	sprintf(rx4Mode, "%d", 26);
	sprintf(tx5Mode, "%d", 4);
	sprintf(rx5Mode, "%d", 24);

	/* Initialize UART1 */
	if ((TX1_Handle = fopen(uart1_tx, "r+")) == NULL) {
		cout << "Can't set up TX1.\n" << endl;
		return -1;
	}
	strcpy(tx1ModeSet, tx1Mode);
	fwrite(&tx1ModeSet, sizeof(char), sizeof(&tx1ModeSet), TX1_Handle);
	fclose(TX1_Handle);
	if ((RX1_Handle = fopen(uart1_rx, "r+")) == NULL) {
		cout << "Can't set up RX1.\n" << endl;
		return -1;
	}
	strcpy(rx1ModeSet, rx1Mode);
	fwrite(&rx1ModeSet, sizeof(char), sizeof(&rx1ModeSet), RX1_Handle);
	fclose(RX1_Handle);

	/* Initialize UART2 */
	if ((TX2_Handle = fopen(uart2_tx, "r+")) == NULL) {
		cout << "Can't set up TX2." << endl;
		return -1;
	}
	strcpy(tx2ModeSet, tx2Mode);
	fwrite(&tx2ModeSet, sizeof(char), sizeof(&tx2ModeSet), TX2_Handle);
	fclose(TX2_Handle);
	if ((RX2_Handle = fopen(uart2_rx, "r+")) == NULL) {
		cout << "Can't set up RX2.\n" << endl;
		return -1;
	}
	strcpy(rx2ModeSet, rx2Mode);
	fwrite(&rx2ModeSet, sizeof(char), sizeof(&rx2ModeSet), RX2_Handle);
	fclose(RX2_Handle);

	/* Initialize UART4 */
	if ((TX4_Handle = fopen(uart4_tx, "r+")) == NULL) {
		cout << "Can't set up TX4" << endl;
		return -1;
	}
	strcpy(tx4ModeSet, tx4Mode);
	fwrite(&tx4ModeSet, sizeof(char), sizeof(&tx4ModeSet), TX4_Handle);
	fclose(TX4_Handle);
	if ((RX4_Handle = fopen(uart4_rx, "r+")) == NULL) {
		cout << "Can't set up RX4.\n" << endl;
		return -1;
	}
	strcpy(rx4ModeSet, rx4Mode);
	fwrite(&rx4ModeSet, sizeof(char), sizeof(&rx4ModeSet), RX4_Handle);
	fclose(RX4_Handle);

	/* Initialize UART5*/
	if ((TX5_Handle = fopen(uart5_tx, "r+")) == NULL) {
		cout << "Can't set up TX5.\n" << endl;
		return -1;
	}
	strcpy(tx5ModeSet, tx5Mode);
	fwrite(&tx5ModeSet, sizeof(char), sizeof(&tx5ModeSet), TX5_Handle);
	fclose(TX5_Handle);
	if ((RX5_Handle = fopen(uart5_rx, "r+")) == NULL) {
		cout << "Can't set up RX5" << endl;
		return -1;
	}
	strcpy(rx5ModeSet, rx5Mode);
	fwrite(&rx5ModeSet, sizeof(char), sizeof(&rx5ModeSet), RX5_Handle);
	fclose(RX5_Handle);
	cout << "Finished initializing." << endl;
	return 1;
}