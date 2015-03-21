/*******************************************************
 * C++ Example code for Lift Operation Simulation using
 * Beaglebone Black running Debian 7 Linux distribution
 ********************************************************/
 
/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* Standard C++ Header Files */
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<csignal>
#include <cstdlib>


using namespace std;

/* Local (Program) Header Files */
#include "gpio.h"
#include "elevator.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"

#define MAX_BUF		1
char *buf[MAX_BUF];

fd_set read_fds;
int max_fd;


string to_string(int a)
{
	ostringstream temp;
	temp<<a;
	return temp.str();
}


void liftLEDExit(string liftLED)
{
	gpioSetValue(liftLED, "0");
	gpioUnexport(liftLED);
}


void liftLEDInit(string liftLED)
{
	gpioExport(liftLED);
	gpioSetDir(liftLED, "out");
	gpioSetValue(liftLED, "0");
}

void liftLEDOn(string liftLED)
{
	gpioSetValue(liftLED, "1");
}

void liftLEDOff(string liftLED)
{
	gpioSetValue(liftLED, "0");
}


void liftButtonExit(string button)
{
	gpioUnexport(button);
}


void liftButtonInit(string button)
{
	gpioExport(button);
	gpioSetDir(button, "in");
	gpioSetEdge(button, "falling");
}




void liftInitAll(void)
{
	unsigned char i;

	for(i=0; i<NO_OF_DIR_LEDS; i++)
			liftLEDInit(to_string(dir_leds[i]));

	for(i=0; i<NO_OF_FLOORS; i++)
	{
		liftLEDInit(to_string(pos_leds[i]));
		liftLEDInit(to_string(lift_leds[i]));
		liftButtonInit(to_string(lift_buttons[i]));
	}

}


void liftExitAll()
{
	unsigned char i;

	for(i=0; i<NO_OF_DIR_LEDS; i++)
			liftLEDExit(to_string(dir_leds[i]));

	for(i=0; i<NO_OF_FLOORS; i++)
	{
		liftLEDExit(to_string(pos_leds[i]));
		liftLEDExit(to_string(lift_leds[i]));
		liftButtonExit(to_string(lift_buttons[i]));
	}

	cout << "\n=== Demonstration END ===\n" << endl;
}

void liftDefaultPos(void)
{
	liftLEDOn(to_string(pos_leds[DEFAULT_LIFT_POS]));
}


void liftDirUp(void)
{
	unsigned char i;

	for(i=0; i<NO_OF_DIR_LEDS; i++)
	{
			liftLEDOn(to_string(dir_leds[i]));
			usleep(1000 * 500);
	}

	for(i=0; i<NO_OF_DIR_LEDS; i++)
		liftLEDOff(to_string(dir_leds[i]));
}

void liftDirDown(void)
{
	char i;

	for(i=NO_OF_DIR_LEDS; i>0; i--)
	{
		liftLEDOn(to_string(dir_leds[i-1]));
		usleep(1000 * 500);
	}

	for(i=0; i<NO_OF_DIR_LEDS; i++)
		liftLEDOff(to_string(dir_leds[i]));

}

int gpioFdOpen(unsigned int gpio)
{
    int fd;

    string gp_num = to_string(gpio);
    string path(SYSFS_GPIO_DIR);
    const char *gp_file = (path + "/gpio" + gp_num + "/value").c_str();

    fd = open(gp_file, O_RDONLY);

    if (fd < 0) {
        perror("gpio/fd_open");
    }

    return fd;
}


void liftButtonOpen(void)
{

	unsigned char i;
	int button_fd;

	for(i=0; i<NO_OF_FLOORS; i++)
	{
		button_fd = gpioFdOpen(floor_set[i].button);
		 if (button_fd < 0)
		 {
		        printf("Cannot open file handle for Lift button #%d\n", i);
		        exit(0);
		  }

		floor_set[i].fd = button_fd;
		//printf("fd%d = %d\n",button_fd, floor_set[i].fd);
	}
}

void seekAllButtons()
{
	int i;

	FD_ZERO(&read_fds);
	max_fd = 0;

	for(i=0; i<NO_OF_FLOORS; i++)
	{
		FD_SET(floor_set[i].fd, &read_fds);
		if(floor_set[i].fd > max_fd)
			max_fd = floor_set[i].fd;

		lseek(floor_set[i].fd, 0, SEEK_SET);
		read(floor_set[i].fd, buf, MAX_BUF);
	}
}


int liftGetInput()
{
	int ret=-1, fds;
	unsigned int i;

	seekAllButtons();

	cout << "\nPress any LIFT button..." << endl;

	ret = select(max_fd+1, NULL, NULL, &read_fds, NULL);

	if(ret < 0)
	{
		  perror("select failed");
		  exit(0);
	}

	for(i=0; i<NO_OF_FLOORS; i++)
	{
		fds=floor_set[i].fd;

		if(FD_ISSET(fds, &read_fds))
		{
			cout << "LIFT button is pressed for floor #" << i << endl;
			liftLEDOn(to_string(floor_set[i].led));
			sleep(1);
			ret = i;
			break;
		}
	}
  return ret;
}

void sigfunc(int s)
{
	liftExitAll();
	exit(0);
}


int main(int argc, char* argv[])
{
	int cur_flr, new_flr, tmp;

	cout << "Lift Operation Simulation using C++" << endl;
	cout << "-----------------------------------------------" << endl;
	signal(SIGINT, sigfunc);
	liftInitAll();

	liftButtonOpen();
	liftDefaultPos();

   cur_flr = DEFAULT_LIFT_POS;


	  while(1)
	  {
		  new_flr = liftGetInput();

		  if(new_flr < 0)
			  continue;

		  if(new_flr > cur_flr)
		  {
			  tmp = cur_flr;
			  cout << "LIFT going UP to floor #" << new_flr << endl;
			  while (tmp != new_flr)
			  {

				  liftDirUp();
				  usleep(100);
				  liftLEDOff(to_string(pos_leds[tmp]));
				  tmp++;
	 			  liftLEDOn(to_string(pos_leds[tmp]));
	 			  usleep(1000 * 500);
			  }
		  }
		  else if (new_flr < cur_flr)
		  {
			  tmp = cur_flr;
			  cout << "LIFT going DOWN to floor #" << new_flr << endl;
			  while (tmp != new_flr)
			  {

				liftDirDown();
			 	usleep(100);
			 	liftLEDOff(to_string(pos_leds[tmp]));
			 	tmp--;
			 	liftLEDOn(to_string(pos_leds[tmp]));
			  	usleep(1000 * 500);
			  }
		  }
		  cur_flr = new_flr;
		  liftLEDOff(to_string(lift_leds[new_flr]));
		  sleep(1);
	  }
	  return 0;
}

