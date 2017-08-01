#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>

#include "Serial.h"

namespace rcr {
	
	Serial::Serial(const char *portAddress)
	{
		this->address = portAddress;
		
		this->fd = open(this->address, O_RDWR | O_NOCTTY | O_NDELAY);
		
		if (fd == -1)
		{
			printf("Unable to initialize serial port at address ");
			printf(this->getAddress());
			printf("\n");
		}
		else
		{
			
			printf("Serial port sucessfully initialized at address ");
			printf(this->getAddress());
			printf("\n");
		}
		
		close(fd);
	}
		
	const char* Serial::getAddress(void)
	{
		return this->address;
	}
	
} // namespace rcr