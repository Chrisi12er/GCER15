
#define storrageL_port 0
#define storrageR_port 2
#define collector_port 3
#define sorter_port 1

#define ET_port 3
#define IR_port 0

#define LP_idle 1750
#define LP_down 1900
#define LP_up   0

#define RP_idle 250
#define RP_down 100
#define RP_up   2047

int sorting_curr_sorting=0;
void sort_right()
{
	sorting_curr_sorting=1;
	rps_pause_driving();
	set_servo_position(storrageR_port,RP_down);
	set_servo_position(sorter_port,140);
	msleep(400);
	set_servo_position(sorter_port,1150);
	set_servo_position(storrageR_port,RP_idle);
	msleep(300);
	set_servo_position(storrageR_port,RP_idle+150);
	msleep(100);
	set_servo_position(storrageR_port,RP_idle);
	rps_continue_driving();
	sorting_curr_sorting=0;
}

void sort_left()
{
	sorting_curr_sorting=1;
	rps_pause_driving();
	set_servo_position(storrageL_port,LP_down);
	set_servo_position(sorter_port,1880);
	msleep(400);
	set_servo_position(sorter_port,1150);
	set_servo_position(storrageL_port,LP_idle);
	msleep(300);
	set_servo_position(storrageL_port,LP_idle-150);
	msleep(100);
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
		set_servo_position(collector_port,1480);
		msleep(200);
		set_servo_position(collector_port,1370);
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
	set_servo_position(storrageR_port,RP_up-200); msleep(100);
	set_servo_position(storrageR_port,RP_up);     msleep(100);
	set_servo_position(storrageR_port,RP_up-200); msleep(100);
	set_servo_position(storrageR_port,RP_up);     msleep(100);
	set_servo_position(storrageR_port,RP_up-200); msleep(100);
	set_servo_position(storrageR_port,RP_up);     msleep(100);
	set_servo_position(storrageR_port,RP_idle);   msleep(600);
	
	if(sort_state==1){sorting_sort();}
}

void sorting_unload_left()
{
	int sort_state=sorting_sort_stop();
	
	set_servo_position(storrageL_port,LP_up);     msleep(600);
	set_servo_position(storrageL_port,LP_up+200); msleep(100);
	set_servo_position(storrageL_port,LP_up);     msleep(100);
	set_servo_position(storrageL_port,LP_up+200); msleep(100);
	set_servo_position(storrageL_port,LP_up);     msleep(100);
	set_servo_position(storrageL_port,LP_up+200); msleep(100);
	set_servo_position(storrageL_port,LP_up);     msleep(100);
	set_servo_position(storrageL_port,LP_idle);   msleep(600);
	
	if(sort_state==1){sorting_sort();}
}









void sorting_init()
{
	enable_servos();
	set_servo_position(storrageL_port,LP_idle);
	set_servo_position(storrageR_port,RP_idle);
	set_servo_position(collector_port,1600);
	set_servo_position(sorter_port,1150);
	
}






























































