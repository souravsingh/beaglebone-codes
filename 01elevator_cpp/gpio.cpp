/*******************************************************
 * C++ code for GPIO Functions for Lift Simulation using
 * Baglebone Black running Debian 7 Linux distribution
 ********************************************************/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;


#define SYSFS_GPIO_DIR "/sys/class/gpio"


void gpioExport(string gpio)
{
	   fstream fs;
	   string path(SYSFS_GPIO_DIR);
	   fs.open((path + "/export").c_str(), fstream::out);
	   fs << gpio;
	   fs.close();
}


void gpioUnexport(string gpio)
{
	   fstream fs;
	   string path(SYSFS_GPIO_DIR);
	   fs.open((path + "/unexport").c_str(), fstream::out);
	   fs << gpio;
	   fs.close();
}

void gpioSetDir(string gpio, string dir)
{
	   fstream fs;
	   string path(SYSFS_GPIO_DIR);
	   fs.open((path + "/gpio" + gpio + "/direction").c_str(), fstream::out);
	   fs << dir;
	   fs.close();
}


void gpioSetEdge(string gpio, string edge)
{
	   fstream fs;
	   string path(SYSFS_GPIO_DIR);
	   fs.open((path + "/gpio" + gpio + "/edge").c_str(), fstream::out);
	   fs << edge;
	   fs.close();
}

void gpioSetValue(string gpio, string val)
{
	   fstream fs;
	   string path(SYSFS_GPIO_DIR);
	   fs.open((path + "/gpio" + gpio + "/value").c_str(), fstream::out);
	   fs << val;
	   fs.close();
}

