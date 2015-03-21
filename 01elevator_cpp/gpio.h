
/*******************************************************
 * Header File for GPIO Functions for Baglebone Black
 * running Debian 7 Linux distribution
 ********************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

void gpioExport(string gpio);
void gpioUnexport(string gpio);
void gpioSetDir(string gpio, string dir);
void gpioSetValue(string gpio, string val);
void gpioSetEdge(string gpio, string edge);

#endif
