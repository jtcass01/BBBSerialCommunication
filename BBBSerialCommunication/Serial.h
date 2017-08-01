/*
 * uart.h
 *
 *  Created on: Aug 1, 2017
 *      Author: Jacob Cassady
 */

#ifndef RCR_SERIAL_H_
#define RCR_SERIAL_H_

namespace rcr {
	class Serial
	{
	public:
		Serial(const char *portAddress);
		
		const char* getAddress(void);
		
		
	private:
		const char *address;
		int fd;
	};	
}

#endif // !RCR_SERIAL_H_
