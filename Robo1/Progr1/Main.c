#include "math.h"
#include "Camera.h"
#include "RPS.h"
#include "Sorting.h"



int main()
{
	
	cam_init();
	sorting_init();
	rps_init(805,210,90);
	rps_draw_start();
	
	while(!a_button()){msleep(50);}
	
	rps_go_to_position( 805, 600); rps_wait_for();
	sorting_collector_move();
	sorting_sort();
	rps_go_to_position( 805,1300); rps_wait_for();
	rps_go_to_position( 650,1700); rps_wait_for();
	sorting_collector_open();
	rps_go_to_position( 300,1800); rps_wait_for();
	sorting_collector_move();
	rps_go_to_position( 280,1900); rps_wait_for();
	rps_go_to_position( 300,2000); rps_wait_for();
	rps_go_to_position( 350,2100); rps_wait_for();
	rps_go_to_position( 500,2100); rps_wait_for();
	sorting_unload_left();
	rps_go_to_position( 600,1900); rps_wait_for();
	rps_go_to_position( 750, 400); rps_wait_for();
	
	rps_rotate_to_angle(0);
	drive_for(-100,-100,1000); rps_set_gx(215); rps_set_ga(0);
	sorting_unload_right();
	
	rps_go_to_position( 300, 400); rps_wait_for();
	rps_go_to_position( 300,1800); rps_wait_for();
	
	/*
	rps_init(0,0,0);
	while(!a_button()){msleep(50);}
	
	rps_go_to_position(1000,0);
	rps_wait_for();
	//rps_rotate_to_angle_a(-360*5);
	*/
	
	
	/*
	rps_init(800,200,90);
	rps_draw_start();
	while(!a_button()){msleep(50);}
	
	rps_go_to_position(800,500);
	rps_wait_for();
	rps_go_curve(1100,500, ga);
	rps_wait_for();
	rps_go_curve(1500,500, ga);
	rps_wait_for();
	*/
	
	/*
	rps_init(500,500,-90);
	rps_draw_start();
	while(!a_button()){msleep(50);}
	
	rps_go_curve(800,500, ga);
	rps_wait_for();
	//rps_go_curve(1100,500, ga);
	//rps_wait_for();
	*/
	
	
	
	
	msleep(100000);
	return 0;
}


































