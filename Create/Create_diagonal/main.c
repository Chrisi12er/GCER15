// Created on Do März 12 2015
#include <stdio.h>
#include <string.h>

#include "./Create/Claw.h"
#include "./Create/move.h"
#include "./Create/camera.h"
#include "./Create/morse.h"

//3er 11 of 16
//5er 11 of 11
//7er 15 of 16
//9er 12 of 12
//11er 12 of 12
//13er 12 of 12
//15er 14 of 16


//cube and 2 gold poms in bin
//two cubes in bin
//take botguy, put on ground
//take frisbee, put in right endzone



int main()
{
	//startup
	
	clear_motor_position_counter(motclawport);
	set_cor();
	create_connect();
	create_full();
	enable_servos();
	
	
	////////////////////////////////
	
	//positioning	
	
	
	instant_servo(fbarm,0);
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
	
	while(!digital(15) && !a_button())
	{
		msleep(50);
	}
	
	movearm(5);
	
	while(!digital(15) && !a_button())
	{
		msleep(50);
	}
///*	
	movearm(startheight);
	create_spin_CW(50);
	msleep(800);
	create_stop();
	
	set_c_button_text("Light");
	set_b_button_text("Push");
	while(1)
	{
		if(c_button())
		{
			wait_for_light(5);
			break;
		}
		
		if(b_button())
		{
			while(!digital(15) && !a_button())
			{
				msleep(50);
			}
			break;
		}
		msleep(10);
	}

	shut_down_in(119);
	starting_time=seconds();
	
	//////////////////////////////////
	
	//instant_servo(fbarm,500);
	create_spin_CCW(50);
	msleep(800);
	create_stop();
	//claw(copen);
	msleep(2000);
	//movearm(10);
	movearm(5);
//*	
	drive(100,-60);
	claw(ctwocubes);	

	drive(100,60);
	movearm(topheight);
	turn(300,30);
	turn(300,90);

	drive(100,-60);
	
	drive(300,150);			//old value 620!!!!!
	turn(100,30);
	
	while (get_time() < 14)
		{
			msleep(50);
		}
	
	drive(300,600);
	turn(100,60);
	drive(300,280);
	//drive(100,250);
	
	//at mesa
	
	//poms & cube
	
	turn(100,50);			//old value 45!!!
	movearm(boardheight);
	mrp(motarmport,1000,-50);
	turn(50,70);			//old value 65!!!
	movearm(topheight);
	
	create_drive(-100,-250);
	msleep(1000);
	create_stop();
	
	turn(100,20);			//old value 25
	drive(100,-20);
	movearm_thread(boardheight+5);
	msleep(1000);

	claw(copen);
	
	wait_for_arm();
	movearm(topheight);
	wait_for_claw();
	drive(100,20);
	
	
	turn(100,-30);			//old value 35
	drive(100,50);
	create_drive(100,-250);
	msleep(1000);
	create_stop();
	
	drive(100,30);	
	
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
	//mrp(motarmport,1000,200);
	turn(100,-88);
	claw(copen);
	
	//drive(100,-50);
	movearm(topheight);
	mrp(motarmport,1000,300);
	drive(100,-30);
	camera_open();
	findbotguycolor();
	drive(100,200);
	
	if(botguycolor==greenchannel)
	{
		drive(100,200);
		movearm(startheight);
		drive(300,-400);
		
		while (get_time() < 60)
		{
			msleep(50);
		}
		
		turn(100,-10);
		//turn(100,15);
		drive(300,-700);
		claw(copen);
		//drive(300,600);
		//turn(100,15);
		
		movearm_thread(topheight);
		drive(300,-100);
		turn(100,-75);
		drive(100,-200);
		drive(300,500);
		
		while (get_create_rbump()==0 && get_create_lbump()==0)
		{
			create_drive_straight(100);
		}
		create_stop();
		
		//drive(100,-200);
		turn(100,-90);

		//drive(100,-120);
	
		//at mesa
	
		drive(100,-100);
		
		movearm(boardheight);
		mrp(motarmport,1000,-500);
		bmd(motarmport);
		
		while (!digital(8))
		{
			create_drive_straight(-100);
		}
		create_stop();
		
		smooth_servo(fbarm, 1370,2);
		msleep(2000);
		instant_servo(fbclaw, 2000);
		msleep(1000);
		smooth_servo(fbarm,0,2);
		msleep(1000);
		turn(100,90);
		//drive(100,-300);					//previously 150
	//	smooth_servo(fbarm,500,1);
		
		turn(100,90);
		drive(100,-100);
		movearm_thread(5);
		smooth_servo(fbarm,2000,2);
		msleep(100);
		smooth_servo(fbclaw,0,2);
		
		
		
		movearm(topheight);
		instant_servo(fbarm,0);
		drive(300,-100);
		turn(300,90);
		drive(100,50);
		turn(100,-30);
		
		create_drive_straight(-100);
		msleep(250);
		create_stop();
		
		movearm(5);
		claw(cclosed);
		
		movearm(topheight);
		turn(300,-45);
		claw_thread(copen);
		
		
		
	}
	
	else
	{
		//botguy
		
		if(!color_found)
		{drive(50,-130);}
		
		mrp(motarmport,1000,400);
		
		drive(100,100);
		turn(100,90);
		turn(100,45);
		movearm(startheight);
		claw(copen);
		//msleep(1500);
		movearm_thread(topheight);
		msleep(500);
		turn(100,45);
		drive(300,270);	
		
		//frisbee
		
		turn(100,-95);
		drive(300,-250);
		drive(100,-150);
		drive(100,80);
		turn(100,90);
		movearm(startheight);
		instant_servo(fbarm,0);
		drive(300,850);		//value change 700 to 1000 in bg-fb
		
		turn(100,90);
		movearm_thread(topheight);
	
		while (get_create_rbump()==0 && get_create_lbump()==0)
		{
			create_drive_straight(100);
		}
		create_stop();
		
		wait_for_arm();
		//drive(100,-200);
		turn(100,-95);

		//drive(100,-120);
		
		//at mesa
		
		movearm(boardheight);
		mrp(motarmport,1000,-500);
		bmd(motarmport);
		
		while (!digital(8))
		{
			create_drive_straight(-100);
		}
		create_stop();
		
		smooth_servo(fbarm, 1370,2);
		msleep(2000);
		instant_servo(fbclaw, 2000);
		msleep(1000);
		smooth_servo(fbarm,0,2);
		msleep(1000);
		turn(100,97);
		drive(100,-150);
		//smooth_servo(fbarm,500,1);
		
		movearm(startheight);
		turn(100,-94);
		
		drive(300,-800);
		//turn(100,30);
		movearm_thread(5);
		smooth_servo(fbarm,2000,2);
		msleep(100);
		smooth_servo(fbclaw,0,2);
	}
	
		
	
	//poms
/*	
	turn(300,90);
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
*/	

	

	
	//frisbee
	
//////////

/*	
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
		movearm(startheight);
		turn(100,-90);
		
		drive(300,-800);
		movearm(5);
		smooth_servo(fbarm,2000,2);
		msleep(1500);
		smooth_servo(fbclaw,0,2);
	}
*/		


/*	
	drive(100,80);
	turn(100,90);
	movearm(startheight);
	drive(300,850);		//value change 700 to 1000 in bg-fb
	
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
		movearm(startheight);
		turn(100,-90);
		
		drive(300,-800);
		movearm(5);
		smooth_servo(fbarm,2000,2);
		msleep(1500);
		smooth_servo(fbclaw,0,2);
	}
*/	
	
	
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
