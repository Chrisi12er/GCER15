

void cam_init()
{
	camera_open();
}

void cam_update()
{
	camera_update();
	camera_update();
	camera_update();
	camera_update();
	camera_update();
}



int cam_get_size(int channel)
{
	if(get_object_count(channel)==0){return 0;}
	else{return get_object_area(channel,0);}
}


int cam_biggest_channel()
{
	cam_update();
	if(cam_get_size(0)>cam_get_size(1)){return 0;}
	else{return 1;}
}



















































