##########################################################
# * Python GPIO Functions for Traffic Signal Simulation
# * using Baglebone Black running Debian 7 Linux distribution
##########################################################

import sys
import os


SYSFS_GPIO_DIR = "/sys/class/gpio"


def gpioUnexport (gpio):
	try: 
   		fo = open(SYSFS_GPIO_DIR + "/unexport","w")  
   		fo.write(gpio)
   		fo.close()
   		return
   	except IOError:
 		return
             	

def gpioExport (gpio): 
	try:
   		fo = open(SYSFS_GPIO_DIR + "/export","w")  
   		fo.write(gpio)
   		fo.close()
   		return
   	except IOError:
                return


def gpioSetDir (gpio, flag):
	try: 
	   	fo = open(SYSFS_GPIO_DIR + "/gpio" + gpio + "/direction" ,"w")  
	   	fo.write(flag)
	   	fo.close()
	   	return
 	except IOError:
                return


def gpioSetVal (gpio, val):
	try: 
		fo = open(SYSFS_GPIO_DIR + "/gpio" + gpio + "/value" ,"w")  
		fo.write(val)
		fo.close()
		return
	except IOError:
                return


def gpioSetEdge (gpio, flag): 
	try:
		fo = open(SYSFS_GPIO_DIR + "/gpio" + gpio + "/edge" ,"w")  
		fo.write(flag)
		fo.close()
   		return
	except IOError:
                return

