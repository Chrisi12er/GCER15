#include "math.h"
#include "Camera.h"
#include "RPS.h"
#include "Sorting.h"


int wfl=0;
int gop=1;
int drs=1;
//int    ;
//int    ;
void Initialisation(float mmx, float mmy, float da)
{
	cam_init();
	sorting_init();
	rps_init(mmx,mmy,da); rps_speed_percent=100.0;
	
	extra_buttons_show();
	if(wfl){set_x_button_text("WFL [!]");} else{set_x_button_text("WFL [X]");}
	if(gop){set_y_button_text("GOP [!]");} else{set_y_button_text("GOP [X]");}
	if(drs){set_z_button_text("DRS [!]");} else{set_z_button_text("DRS [X]");}
	//if(   ){set_a_button_text("--- [!]");} else{set_a_button_text("--- [X]");}
	//if(   ){set_b_button_text("--- [!]");} else{set_b_button_text("--- [X]");}
	
	set_c_button_text("<Start>");
	
	while(1)
	{
		if(x_button_clicked()){wfl=!wfl; if(wfl){set_x_button_text("WFL [!]");} else{set_x_button_text("WFL [X]");}}
		if(y_button_clicked()){gop=!gop; if(gop){set_y_button_text("GOP [!]");} else{set_y_button_text("GOP [X]");}}
		if(z_button_clicked()){drs=!drs; if(drs){set_z_button_text("DRS [!]");} else{set_z_button_text("DRS [X]");}}
		//if(a_button_clicked()){   =!   ; if(   ){set_a_button_text("--- [!]");} else{set_a_button_text("--- [X]");}}
		//if(b_button_clicked()){   =!   ; if(   ){set_b_button_text("--- [!]");} else{set_b_button_text("--- [X]");}}
		
		if(c_button_clicked()){break;}
		msleep(10);
	}
	
	if(wfl){wait_for_light(1);}
	if(gop){rps_draw_start();}
	
	msleep(100);
}







#define MODE 1

int main()
{
	#if MODE == 1
	Initialisation(700,210,90);
	
	//1.
	rps_go_to_position( 700, 600); rps_wait_for();
	sorting_collector_move(); if(drs){sorting_sort();}
	rps_go_to_position( 700,2000); rps_wait_for();
	rps_go_to_position_back( 700,2400); rps_wait_for();
	
	rps_set_gy(2400-230); rps_set_ga(-90);
	sorting_unload_right();
	
	drive_for(100,100,500);
	rps_go_to_position( 700, 400); rps_wait_for();
	rps_go_to_position_back( 700,0); rps_wait_for();
	
	rps_set_gy(230); rps_set_ga(90);
	sorting_unload_left();
	
	//2.
	rps_go_to_position( 300,1680-100); rps_wait_for();
	rps_rotate_to_angle(90);
	rps_go_to_position( 300,1680); rps_wait_for();
	rps_go_to_position( 500,2000); rps_wait_for();
	
	
	#elif MODE==2
	rps_init(0,0,0);
	//rps_draw_start();
	while(!a_button()){msleep(50);}
	
	rps_rotate_to_angle_a(360*5);
	//rps_go_to_position(1000,0);
	rps_wait_for();
	
	#elif MODE==3
	sorting_init();
	while(1)
	{
		if(a_button()){sort_left ();}
		if(b_button()){sort_right();}
		
		msleep(100);
	}
	
	
	
	#endif
	
	
	
	
	msleep(100000);
	return 0;
}


































