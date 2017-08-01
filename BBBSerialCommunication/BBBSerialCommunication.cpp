#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
using namespace std;
 
struct termios config;
int fd;

int main(int argc, char *argv[]) {
	const char *device = "/dev/ttyS2";
	
	fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		printf("failed to open port\n");
	}
	else
	{
		printf("The port was successfully opened.\n");
	}
	
	close(fd);

}