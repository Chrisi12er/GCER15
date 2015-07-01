
#define storrageL_port 0
#define storrageR_port 2
#define collector_port 3
#define sorter_port 1

#define ET_port 3
#define IR_port 0


#define C_move1  1400
#define C_move2  1600
#define C_open   1300
#define C_closed 2047

#define S_idle 1070
#define S_left 2047
#define S_right 200

#define LP_idle 420
#define LP_down 220
#define LP_up  2047

#define RP_idle 1600
#define RP_down 1820
#define RP_up   0

int sorting_curr_sorting=0;
void sort_right()
{
	sorting_curr_sorting=1;
	rps_pause_driving();
	set_servo_position(storrageR_port,RP_down);
	set_servo_position(sorter_port,S_right);
	msleep(300);
	set_servo_position(sorter_port,S_idle);
	msleep(200);
	set_servo_position(storrageR_port,RP_idle);
	rps_continue_driving();
	sorting_curr_sorting=0;
}

void sort_left()
{
	sorting_curr_sorting=1;
	rps_pause_driving();
	set_servo_position(storrageL_port,LP_down);
	set_servo_position(sorter_port,S_left);
	msleep(300);
	set_servo_position(sorter_port,S_idle);
	msleep(250);
	set_servo_position(storrageL_port,LP_idle);
	rps_continue_driving();
	sorting_curr_sorting=0;
}

void sort_by_color()
{
	if(cam_biggest_channel()==0){sort_right();}
	else{sort_left();}
}


//-----------------------------------------------collector
thread sorting_col_thread_id;
int sorting_col_thread_using=0;

void sorting_collector_move_function()
{
	while(1)
	{
		set_servo_position(collector_port,C_move1);
		msleep(200);
		set_servo_position(collector_port,C_move2);
		msleep(200);
	}
}

void sorting_collector_move()
{
	sorting_col_thread_using=1;
	sorting_col_thread_id=thread_create(sorting_collector_move_function);
	thread_start(sorting_col_thread_id);
}

void sorting_collector_move_stop()
{
	if(sorting_col_thread_using==1){thread_destroy(sorting_col_thread_id);}
	sorting_col_thread_using=0;
}

void sorting_collector_open()
{
	sorting_collector_move_stop();
	set_servo_position(collector_port,1700);
}

void sorting_collector_close()
{
	sorting_collector_move_stop();
	set_servo_position(collector_port,700);
}


//-----------------------------------------------sorter
thread sorting_sort_thread_id;
int sorting_sort_thread_using=0;
void sorting_sort_function()
{
	while(1)
	{
		while(analog_et(ET_port)>600 && analog(IR_port)>250)
		{msleep(100);}
		sort_by_color();
	}
}

void sorting_sort()
{
	sorting_sort_thread_using=1;
	sorting_sort_thread_id=thread_create(sorting_sort_function);
	thread_start(sorting_sort_thread_id);
}

int sorting_sort_stop()
{
	int ret=sorting_sort_thread_using;
	if(sorting_sort_thread_using==1)
	{
		thread_destroy(sorting_sort_thread_id);
		if(sorting_curr_sorting==1){set_servo_position(sorter_port,1150); msleep(300); sorting_curr_sorting=0;}
	}
	sorting_sort_thread_using=0;
	return ret;
}



//-----------------------------------------------unload
void sorting_unload_right()
{
	int sort_state=sorting_sort_stop();
	
	set_servo_position(storrageR_port,RP_up);     msleep(600);
	set_servo_position(storrageR_port,RP_up+200); msleep(100);
	set_servo_position(storrageR_port,RP_up);     msleep(100);
	set_servo_position(storrageR_port,RP_up+200); msleep(100);
	set_servo_position(storrageR_port,RP_up);     msleep(100);
	set_servo_position(storrageR_port,RP_up+200); msleep(100);
	set_servo_position(storrageR_port,RP_up);     msleep(100);
	set_servo_position(storrageR_port,RP_idle);   msleep(600);
	
	if(sort_state==1){sorting_sort();}
}

void sorting_unload_left()
{
	int sort_state=sorting_sort_stop();
	
	set_servo_position(storrageL_port,LP_up);     msleep(600);
	set_servo_position(storrageL_port,LP_up-200); msleep(100);
	set_servo_position(storrageL_port,LP_up);     msleep(100);
	set_servo_position(storrageL_port,LP_up-200); msleep(100);
	set_servo_position(storrageL_port,LP_up);     msleep(100);
	set_servo_position(storrageL_port,LP_up-200); msleep(100);
	set_servo_position(storrageL_port,LP_up);     msleep(100);
	set_servo_position(storrageL_port,LP_idle);   msleep(600);
	
	if(sort_state==1){sorting_sort();}
}









void sorting_init()
{
	enable_servo(collector_port); set_servo_position(collector_port,C_open);
	enable_servo(storrageL_port); set_servo_position(storrageL_port,LP_down);
	enable_servo(storrageR_port); set_servo_position(storrageR_port,RP_down);
	msleep(1000);
	enable_servo(sorter_port   ); set_servo_position(sorter_port,S_idle);
	msleep(300);
	set_servo_position(storrageL_port,LP_idle);
	set_servo_position(storrageR_port,RP_idle);
	
}






























































