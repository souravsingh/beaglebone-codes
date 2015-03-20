/*******************************************************
 * C++ Example code for Traffic Signal Simulation using
 * Beaglebone Black running Debian 7 Linux distribution
 ********************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<csignal>
#include <cstdlib>

using namespace std;

#include "gpio.h"
#include "traffic_light.h"

string to_string(int a)
{
	ostringstream temp;
	temp<<a;
	return temp.str();
}


void lightExit(string light)
{
	gpioSetValue(light, "0");
	gpioUnexport(light);
}


void lightInit(string light)
{
	gpioExport(light);
	gpioSetDir(light, "out");
	gpioSetValue(light, "0");
}

void lightOn(string light)
{
	gpioSetValue(light, "1");
}

void lightOff(string light)
{
	gpioSetValue(light, "0");
}

void trafficInitAll(void)
{
		lightInit(to_string(NORTH_GREEN));
		lightInit(to_string(NORTH_YELLOW));
		lightInit(to_string(NORTH_RED));

		lightInit(to_string(EAST_GREEN));
		lightInit(to_string(EAST_YELLOW));
		lightInit(to_string(EAST_RED));

		lightInit(to_string(SOUTH_GREEN));
		lightInit(to_string(SOUTH_YELLOW));
		lightInit(to_string(SOUTH_RED));

		lightInit(to_string(WEST_GREEN));
		lightInit(to_string(WEST_YELLOW));
		lightInit(to_string(WEST_RED));
}


void trafficExitAll(void)
{

		lightExit(to_string(NORTH_GREEN));
		lightExit(to_string(NORTH_YELLOW));
		lightExit(to_string(NORTH_RED));

		lightExit(to_string(EAST_GREEN));
		lightExit(to_string(EAST_YELLOW));
		lightExit(to_string(EAST_RED));

		lightExit(to_string(SOUTH_GREEN));
		lightExit(to_string(SOUTH_YELLOW));
		lightExit(to_string(SOUTH_RED));

		lightExit(to_string(WEST_GREEN));
		lightExit(to_string(WEST_YELLOW));
		lightExit(to_string(WEST_RED));

}



void northSouthOn(void)
{
	lightOff(to_string(EAST_YELLOW));
	lightOff(to_string(WEST_YELLOW));
	lightOff(to_string(NORTH_RED));
	lightOff(to_string(SOUTH_RED));


	lightOn(to_string(EAST_RED));
	lightOn(to_string(WEST_RED));

	lightOn(to_string(NORTH_GREEN));
	lightOn(to_string(SOUTH_GREEN));

	sleep(10);

	lightOff(to_string(NORTH_GREEN));
	lightOff(to_string(SOUTH_GREEN));

	lightOn(to_string(NORTH_YELLOW));
	lightOn(to_string(SOUTH_YELLOW));
	sleep(1);
}


void eastWestOn(void)
{
	lightOff(to_string(NORTH_YELLOW));
	lightOff(to_string(SOUTH_YELLOW));
	lightOff(to_string(EAST_RED));
	lightOff(to_string(WEST_RED));


	lightOn(to_string(NORTH_RED));
	lightOn(to_string(SOUTH_RED));

	lightOn(to_string(EAST_GREEN));
	lightOn(to_string(WEST_GREEN));

	sleep(10);

	lightOff(to_string(EAST_GREEN));
	lightOff(to_string(WEST_GREEN));

	lightOn(to_string(EAST_YELLOW));
	lightOn(to_string(WEST_YELLOW));
	sleep(1);

}

void sigfunc(int s)
{
	trafficExitAll();
	std::exit(0);
}

int main(int argc, char* argv[])
{
	cout << "\nTraffic Signal Light Simulation using C++" << endl;
	cout << "-----------------------------------------------" << endl;
	signal(SIGINT, sigfunc);
	trafficInitAll();
	sleep(2);
	for(int i=0; i<10; i++)
	{
		cout << "\nNORTH-SOUTH	--> [GO]" << endl;
		cout << "EAST-WEST 	--> [STOP]\n" << endl;
		northSouthOn();
		sleep(1);
		cout << "\nEAST-WEST 	--> [GO]" << endl;
		cout << "NORTH-SOUTH 	--> [STOP]\n" << endl;
		eastWestOn();
		sleep(1);
	}

	trafficExitAll();
	cout << "Done." << endl;
}


