// Created on So April 19 2015
#include <stdio.h>
#include <string.h>

#include "./Create/Claw.h"
#include "./Create/move.h"
#include "./Create/camera.h"
#include "morse.h"

int main()
{
	create_connect();
	enable_servo(ccport);
	
	create_full();	
	start_morse();
	morse("Botball", 1);
	/*	motor(1,100);
	motor(0,-100);
	motor(1,0);
	msleep(5000);
	motor(3,100);
	wait_for_morse();
	motor(0,0);
	motor(3,0);
	*/
	
	create_disconnect();
}
