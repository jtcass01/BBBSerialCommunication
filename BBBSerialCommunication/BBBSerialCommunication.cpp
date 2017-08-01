#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>

#include "Serial.h"

using namespace std;
 
struct termios config;

rcr::Serial UART0 = rcr::Serial("/dev/ttyS0");
rcr::Serial UART1 = rcr::Serial("/dev/ttyS1");
rcr::Serial UART2 = rcr::Serial("/dev/ttyS2");
rcr::Serial UART3 = rcr::Serial("/dev/ttyS3");
rcr::Serial UART4 = rcr::Serial("/dev/ttyS5");

int main(int argc, char *argv[]) {

}