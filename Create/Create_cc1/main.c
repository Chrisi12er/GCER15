// Created on Do März 12 2015
#include <stdio.h>
#include <string.h>

#include "./Create/Claw.h"
#include "./Create/move.h"
#include "./Create/camera.h"
#include "./Create/morse.h"

//3er 10 of 16
//5er 11 of 11
//7er 16 of 16
//9er 11 of 12
//11er 12 of 12
//13er 11 of 12
//15er 13 of 16


//dispose cable carrier
//cube and 2 gold poms in bin
//two cubes in bin
//take botguy, put on ground



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
	
	instant_servo(ccport, ccup);
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
	
	instant_servo(fbarm,0);
	create_spin_CCW(50);
	msleep(800);
	create_stop();
	//claw(copen);
	msleep(2000);
	//movearm(10);
	movearm(5);
//***	
	drive(100,-60);
	claw(ctwocubes);	

	drive(100,60);
	movearm(topheight);
	turn(300,30);
	turn(300,90);

	drive(100,-60);

	//diagonal
	
	movearm_thread(startheight);
	drive(300,200);
	turn(100,30);
	drive(300,900);
	turn(100,55);
	drive(100,140);
	
	//msleep(5000);
	
	
	

	//arc
/*	
	mrp(motarmport,1000,200);
	
	drive(300,300);
	create_drive(300,-700);
	msleep(1900);
	create_stop();
	movearm_thread(startheight);
	msleep(1000);
	create_drive(300,-700);
	msleep(1900);
	create_stop();

	//msleep(5000);
*/	


	////corners
/*	
	drive(300,(600-250));			//old value 620!!!!!
	turn(300,90);
	drive(100,-120);
	//msleep(500);
	movearm_thread(startheight);
	drive(300,670);
	
	//due to lights:
	
	turn(100,-90);
	drive(300,250);
	
	//////
	
	turn(100,-90);
	wait_for_arm();
	drive(300,450);
	turn(100,90);
	drive(100,150);
*/	
	
	instant_servo(ccport, ccdown);
	
	//msleep(5000);
	
	drive(300,-200);
	drive(300,200);
	
	//wait for Platform
	
	drive(300,-600);
	msleep(5000);
	drive(300,600);
	
	//
	
	//drive(100,-150);
	
	turn(100,-90);
	drive(300,-300);
	movearm_thread(topheight);
	turn(100,90);
	wait_for_arm();
	
	while (get_create_rbump()==0 && get_create_lbump()==0)
		{
			create_drive_straight(100);
		}
		create_stop();
	
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
	
	turn(100,25);			//old value 35
	drive(100,-20);
	movearm(boardheight+5);

	claw(copen);
	
	movearm(topheight);
	wait_for_claw();
	drive(100,20);
	
	
	turn(100,-35);
	drive(100,50);
	create_drive(100,-250);
	msleep(1000);
	create_stop();
	
	
	
	turn(100,65);
	drive(100,-100);
	
	
	//botguy
	
	//drive(100,50);
	//turn(100,90);
	//drive(100,130);
	//turn(100,90);
	//drive(100,-100);
	drive(300,420);
	//mrp(motarmport,1000,200);
	turn(100,-90);
	claw(copen);
	//drive(100,-50);
	movearm(topheight);
	mrp(motarmport,1000,300);
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
		turn(100,-92);

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
		turn(100,94);
		//drive(100,-300);					//previously 150
	//	smooth_servo(fbarm,500,1);
		
		turn(100,90);
		drive(100,-100);
		movearm_thread(5);
		smooth_servo(fbarm,2000,2);
		msleep(100);
		smooth_servo(fbclaw,0,2);
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
		turn(100,30);
		movearm_thread(5);
		smooth_servo(fbarm,2000,2);
		msleep(100);
		smooth_servo(fbclaw,0,2);
	}
	
	
	
	claw(copen);
	claw(cclosed);
	
//claw(cclosed);	
create_disconnect(); 


}


