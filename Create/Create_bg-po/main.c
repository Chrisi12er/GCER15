// Created on Do März 12 2015

#include "./Create/Claw.h"
#include "./Create/move.h"
#include "./Create/camera.h"

//3er 9 of 16
//5er 11 of 11
//7er 16 of 16
//9er 11 of 12
//11er 12 of 12
//13er 11 of 12
//15er 13 of 16


//cube and 2 gold poms in bin
//two cubes in bin
//take botguy, put on ground
//2 gold poms in bin
//take frisbee, put in right endzone



int main()
{
	//startup
	
	clear_motor_position_counter(motclawport);
	set_cor();
	create_connect();
	enable_servos();
	
	
	////////////////////////////////
	
	//positioning	
	
	
	instant_servo(fbarm,500);
	instant_servo(fbclaw,0);
	//instant_servo(fbarm,500);
	//instant_servo(fbclaw,0);
	printf("hier\n");
	movearm(topheight);
	printf("da\n");
	
	drive(100,30);
	turn(100,-90);
	turn(100,-30);
	claw(copen);
	movearm(5);
	
	msleep(5000);
///*	
	movearm(160);
	create_spin_CW(50);
	msleep(800);
	create_stop();
	
	//wait_for_light(lightport);
	//shut_down_in(118);
	
	//////////////////////////////////
	
	msleep(5000);
	
	create_spin_CCW(50);
	msleep(800);
	create_stop();
	//claw(copen);
	msleep(2000);
	//movearm(10);
	movearm(5);
//*/	
	drive(100,-60);
	claw(ctwocubes);	

	drive(100,60);
	movearm(topheight);
	turn(300,30);
	turn(300,90);

	drive(100,-60);
	
	drive(300,620);
	turn(300,90);
	drive(100,-80);
	drive(300,670);
	
	//at mesa
	
	//poms & cube
	
	turn(100,45);
	movearm(boardheight);
	mrp(motarmport,1000,-50);
	turn(50,70);
	movearm(topheight);
	
	create_drive(-100,-250);
	msleep(1000);
	create_stop();
	
	turn(100,30);
	drive(100,-20);
	movearm(boardheight+5);

	claw(copen);
	
	movearm(topheight);
	drive(100,20);
	
	
	turn(100,-30);
	drive(100,50);
	create_drive(100,-250);
	msleep(1000);
	create_stop();
	
	
	
	turn(100,65);
	drive(100,-100);
	
	//drive(100,80);
	//turn(100,-90);
	
	//two cubes
	
/*	drive(100,-30);
	create_drive(-100,250);
	msleep(1500);
	create_stop();
	
	turn(100,10);
	drive(100,10);
	movearm(boardheight+5);

	claw(copen);
	
	movearm(topheight);
	drive(100,-10);
	
	
	turn(100,-10);
	
	create_drive(100,250);
	msleep(1500);
	create_stop();
	drive(100,30);
*/	
	//turn(100,90);
	//drive(100,-150);
	
	//////////////////////////////////////////////
	
	//botguy
	
	//drive(100,50);
	//turn(100,90);
	//drive(100,130);
	//turn(100,90);
	//drive(100,-100);
	drive(300,420);
	turn(100,-90);
	claw(copen);
	//drive(100,-50);
	movearm(topheight);
	mrp(motarmport,1000,100);
	camera_open();
	findbotguycolor();
	drive(100,400);
	
	if(botguycolor==greenchannel)
	{
		movearm(160);
		drive(300,-400);
		turn(100,-15);
		//turn(100,15);
		drive(300,-600);
		claw(copen);
		drive(300,600);
		turn(100,15);
		drive(300,500);
		movearm(topheight);
		turn(300,90);
		turn(300,90);
		drive(300,-300);
		drive(100,-100);
		drive(300,600);	
	}
	
	else
	{
		turn(100,90);
		turn(100,45);
		claw(copen);
		turn(300,45);
		drive(300,-300);
		drive(100,-100);
		drive(300,600);	
	}
	
	
	//poms
	
	drive(300,-150);	
	drive(100,-100);
	movearm(topheight);
	mrp(motarmport,1000,50);
	drive(100,80);
	turn(100,65);
	claw(cclosed);
	//turn(100,5);
	drive(100,-20);
	movearm(boardheight);
	mrp(motarmport,1000,-150);
	
	create_spin_CW(20);
	msleep(2500);
	create_stop();
	//drive(100,-50);
	movearm(topheight);
	//mrp(motarmport,1000,-50)
	//drive(100,50);				////////////
	claw(copen);
	movearm(topheight);
	mrp(motarmport,1000,50);
	turn(50,15);
	movearm(boardheight);
	mrp(motarmport,1000,-150);
	claw(cclosed);
	movearm(topheight);
	drive(100,100);
	
	turn(100,-105);
	
	drive(100,-150);
	drive(300,650);
	drive(100,50);
	turn(100,90);
	drive(100,-200);
	turn(100,30);
	
	drive(100,10);
	movearm(boardheight+5);
	claw(copen);
	movearm(topheight);
	drive(100,-10);
	
	turn(100,-30);
	drive(100,50);
	turn(100,90);
	
	drive(100,-100);
	

	
	//frisbee
	
		
	drive(100,80);
	turn(100,90);
	movearm(160);
	drive(300,700);
	
	turn(100,90);
	movearm(topheight);
	
	while (get_create_rbump()==0 && get_create_lbump()==0)
	{
		create_drive_straight(100);
	}
	create_stop();
	
	//drive(100,-200);
	turn(100,-90);

	//drive(100,-120);
	
	//at mesa
	
	movearm(boardheight);
	mrp(motarmport,1000,-50);
	smooth_servo(fbarm, 1800,2);
	msleep(5000);
	instant_servo(fbclaw, 2000);
	msleep(5000);
	movearm(topheight);
	msleep(500);
	smooth_servo(fbarm,700,2);
	msleep(2000);
	turn(100,90);
	drive(100,-150);
	smooth_servo(fbarm,500,1);

	
	if(botguycolor==greenchannel)
	{
		turn(100,90);
		drive(100,-100);
		movearm(5);
		smooth_servo(fbarm,2000,2);
		msleep(1500);
		smooth_servo(fbclaw,0,2);
	}
	
	else
	{
		movearm(160);
		turn(100,-90);
		
		drive(300,-800);
		movearm(5);
		smooth_servo(fbarm,2000,2);
		msleep(1500);
		smooth_servo(fbclaw,0,2);
	}
	
	
	
	claw(copen);
	claw(cclosed);
	
//claw(cclosed);	
create_disconnect(); 


}

/*	//drive(300,650);				//both poms seperately
	//turn(100,90);
	//turn(100,90);
	//drive(100,-100);
	drive(100,100);
	turn(100,90);
	drive(100,-100);
	movearm(boardheight);
	mrp(motarmport,1000,-50);
	
	claw(cclosed);
	movearm(topheight);
	drive(100,100);
	turn(100,-90);
	drive(100,-150);
	drive(300,650);
	drive(100,50);
	turn(100,90);
	drive(100,-150);
	turn(100,30);
	
	drive(100,10);
	movearm(boardheight+5);
	claw(copen);
	movearm(topheight);
	drive(100,-10);
	
	turn(100,-30);
	drive(100,50);
	turn(100,90);
	
	drive(100,-100);
	drive(300,650);
	turn(100,90);
	turn(100,90);
	
	//pom #2
	
	drive(100,-100);
	drive(100,30);
	turn(100,80);
	drive(100,70);
	movearm(boardheight);
	mrp(motarmport,1000,-50);
	
	claw(cclosed);
	movearm(topheight);
	drive(100,-70);
	turn(100,-80);
	drive(100,-80);
	drive(300,650);
	drive(100,50);
	turn(100,90);
	drive(100,-50);
	turn(100,30);
	
	drive(100,10);
	movearm(boardheight+5);
	claw(copen);
	movearm(topheight);
	drive(100,-10);
	
	turn(100,60);
	drive(100,-80);
*/

/*
	movearm(topheight);					//both poms together
	mrp(motarmport,1000,50);
	drive(100,80);
	turn(100,90);
	//turn(100,5);
	drive(100,-20);
	movearm(boardheight);
	mrp(motarmport,1000,-150);
	claw(cclosed);
	movearm(topheight);
	
	drive(100,50);
	turn(100,-15);
	//drive(100,-50);
	movearm(boardheight+5);
	//mrp(motarmport,1000,-50)
	drive(100,-20);				////////////
	claw(copen);
	movearm(boardheight);
	mrp(motarmport,1000,-150);
	claw(cclosed);
	movearm(topheight);
	drive(100,100);
	
	turn(100,-75);
	
	drive(100,-150);
	drive(300,650);
	drive(100,50);
	turn(100,90);
	drive(100,-200);
	turn(100,30);
	
	drive(100,10);
	movearm(boardheight+5);
	claw(copen);
	movearm(topheight);
	drive(100,-10);
	
	turn(100,-30);
	drive(100,50);
	turn(100,90);
	
	drive(100,-100);
*/
