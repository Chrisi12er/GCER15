//------------------------------------------DEFINES

//rps
#define BLACK_MAGIC	0.0520278 	//...
#define tikmmfak	0.1708174 	//...

//lmrorm (>=r <=l)
#define lmtorm		1.01000000


#define rv_corr 
#define rb_corr 
#define lv_corr 
#define lb_corr 


//hardware
#define lm 1
#define rm 3


//graphics
#define graph_size 240
#define graph_tab_size 2400

//colors
#define white 255,255,255
#define black   0,  0,  0
#define red   255,  0,  0
#define green   0,255,  0
#define blue   64,224,208
#define pink  255,105,180

#define robot_length1 70
#define robot_length2 195
#define robot_width  120


//------------------------------------------VARIABLES

float gx,gy,ga;

float tgx,tgy,tga;

float tcgx, tcgy;
float tcmgx, tcmgy, tcradius;
int tcside;

float chx, chy, cha;
int  bchx,bchy,bcha;

int rps_go=0;
int rps_pause=0;
int rps_forward=1;
int rps_drive_curve=0;

float mot_corr=1.0;


thread  draw_thread_id;

float mmtop=(float) (graph_size)/graph_tab_size;

float rlp1=(float) (robot_length1*graph_size/graph_tab_size);
float rlp2=(float) (robot_length2*graph_size/graph_tab_size);
float rwp =(float) (robot_width  *graph_size/graph_tab_size);

//------------------------------------------BASICS
void rps_thread();
void rps_thread_drawing();
void rps_draw_start();


void drive(int ls, int rs)
{
	motor(lm,ls);
	motor(rm,(float)rs*mot_corr);
}

void stop_driving()
{
	freeze(rm);
	freeze(lm);
}

void drive_for(int ls, int rs, float time)
{
	drive(ls,rs);
	msleep(time);
	stop_driving();
}

int dfhls;
int dfhrs;
float dfhtime;
void drive_for_helper()
{drive_for(dfhls,dfhrs,dfhtime);}
void drive_for_thread(int ls, int rs, float time)
{
	dfhls=ls; dfhrs=rs; dfhtime=time;
	thread_start(thread_create(drive_for_helper));
}

float rps_get_mpl()
{return (float) get_motor_position_counter(lm)/lmtorm;}

float rps_get_mpr()
{return (float) get_motor_position_counter(rm)*lmtorm;}


//------------------------------------------RPS

void rps_set_position(float mmx, float mmy, float a)
{
	chx=mmx/tikmmfak; bchx=1;
	chy=mmy/tikmmfak; bchy=1;
	cha=a;			  bcha=1;
}

void rps_set_gx(float mmx)
{chx=mmx/tikmmfak; bchx=1;}

void rps_set_gy(float mmy)
{chy=mmy/tikmmfak; bchy=1;}

void rps_set_ga(float a)
{cha=a; bcha=1;}

void rps_go_to_position(float mmx, float mmy)
{
	tgx=mmx/tikmmfak;
	tgy=mmy/tikmmfak;
	rps_go=1;
	rps_forward=1;
	rps_drive_curve=0;
}

void rps_go_to_position_back(float mmx, float mmy)
{
	tgx=mmx/tikmmfak;
	tgy=mmy/tikmmfak;
	rps_go=1;
	rps_forward=0;
	rps_drive_curve=0;
}

void rps_go_curve(float mx, float my, float sa)
{
	tcgx=mx/tikmmfak;
	tcgy=my/tikmmfak;
	tcradius=calc_radius_point(gx, gy, sa, tcgx, tcgy, &tcmgx, &tcmgy);
	tcside=calc_side_of_point(gx,gy,sa,tcmgx,tcmgy);
	rps_drive_curve=1;
	rps_go=1;
}



void rps_pause_driving()
{
	rps_pause=1;
	stop_driving();
}

void rps_continue_driving()
{
	rps_pause=0;
}

void rps_go_to_x(float mm)
{
	tgx=mm/tikmmfak;
	tgy=gy;
	rps_go=1;
	rps_forward=1;
}

void rps_go_to_y(float mm)
{
	tgx=gx;
	tgy=mm/tikmmfak;
	rps_go=1;
	rps_forward=1;
}

void rps_init(float xx, float yy, float aa)
{
	clear_motor_position_counter(lm);
	clear_motor_position_counter(rm);
	
	float lm_dpos=rps_get_mpl();
	float rm_dpos=rps_get_mpr();
	
	drive(100,100);
	msleep(1000);
	stop_driving();
	msleep(200);
	
	lm_dpos=rps_get_mpl()-lm_dpos;
	rm_dpos=rps_get_mpr()-rm_dpos;
	
	msleep(500);
	drive(-100,-100);
	msleep(1000);
	stop_driving();
	msleep(200);
	
	mot_corr=lm_dpos/rm_dpos;
	
	printf("Init RPS! [%f]\n",mot_corr);
	rps_set_position(xx, yy, aa);
	thread_start(thread_create(rps_thread));
	
	msleep(2000);
	
}

float get_time();
void rps_rotate_to_angle_v(float aa, int regulate)
{
	float diff;
	float stime=seconds();
	
	while(1)
	{
		if(regulate) {diff=clamp_angle(ga-aa,-180);}
		else         {diff=ga-aa;}
		
		if(pos(diff)>2)
		{
			if(diff>0){diff=max(min(diff*2, 100), 70);}
			if(diff<0){diff=min(max(diff*2,-100),-70);}
			drive(diff,-diff);
		}
		
		else
		{
			stop_driving();
			msleep(100);
			if(pos(diff)<2){printf("Reached RPS rotation at: %f°\n", ga); break;}
		}
		/*
		if(seconds()-stime>10.0)
		{
			stop_driving();
			msleep(100);
			break;
		}
		*/
		msleep(10);
	}
}

void rps_rotate_to_angle(float aa)
{rps_rotate_to_angle_v(aa,1);}

void rps_rotate_to_angle_a(float aa)
{
	rps_rotate_to_angle_v(aa,0);
}

void rps_rotate_to_position(float xx, float yy)
{
	rps_rotate_to_angle(atand2(yy-gy*tikmmfak,xx-gx*tikmmfak));
}

void rps_wait_for()
{
	while(rps_go==1){msleep(100);}
}

int tiktopx(float mm){return (int)(mm*tikmmfak*mmtop);}
int tiktopy(float mm){return (int)(graph_size-mm*tikmmfak*mmtop);}
int mmtopx (float mm){return (int)(mm*mmtop);}
int mmtopy (float mm){return (int)(graph_size-mm*mmtop);}

//------------------------------------------THREADS

float rps_speed_percent=100.0;

void rps_thread()
{
	//Init Tracking
	float da, dist;
	float dmpr, dmpl;
	
	float nmpl=rps_get_mpl();
	float nmpr=rps_get_mpr();
	float ompl=nmpl;
	float ompr=nmpr;
	
	//Init Driving
	float RemLenght;
	float PathAngle;
	float atm, rms, lms;
	int counter=0;
	
	
	while(1)
	{
		
		//Set Values
		if(bchx){gx=chx; bchx=0;}
		if(bchy){gy=chy; bchy=0;}
		if(bcha){ga=cha; bcha=0;}
		
		//Tracking
		nmpl=rps_get_mpl();
		nmpr=rps_get_mpr();
		dmpl=nmpl-ompl; ompl=nmpl;
		dmpr=nmpr-ompr; ompr=nmpr;
		
		da  =(float)((dmpr-dmpl)*BLACK_MAGIC);
		dist=(float)((dmpr+dmpl)*0.5);
		
		gx+=dist*cosd(ga+(da*0.5));
		gy+=dist*sind(ga+(da*0.5));
		ga+=da;
		
		//Driving
		if(rps_go==1 && rps_pause==0)
		{
			//Circle
			if(rps_drive_curve==1)
			{
				float at=atand2(tcgy-tcmgy,tcgx-tcmgx);
				float as=atand2(  gy-tcmgy,  gx-tcmgx);
				float length;
				
				length=clamp_angle(as-at, 0.0);
				if(length>180.0){length=360.0-length;}
				length=pos(2.0*tcradius*length/360.0);
				
				float tangle;
				if(tcside==1){tangle=as-90.0;}
				else         {tangle=as+90.0;}
				
				tgx=tcmgx+pos(tcradius)*cosd(as)+length*cosd(tangle);
				tgy=tcmgy+pos(tcradius)*sind(as)+length*sind(tangle);
			}
			
			
			RemLenght=pytag(tgx-gx,tgy-gy);
			if(RemLenght>5.0/tikmmfak)
			{
				if(rps_forward)
				{			
					PathAngle=atand2(tgy-gy,tgx-gx)-ga;
					PathAngle=clamp_angle(PathAngle,-180);
					atm=PathAngle*4.0;
					     if(atm>0){atm+=10;}
					else if(atm<0){atm-=10;}
					atm=minmax(-200,atm,200);
					
					rms=minmax(100,100+atm,-100);
					lms=minmax(100,100-atm,-100);
				}
				else
				{
					PathAngle=atand2(tgy-gy,tgx-gx)-(ga+180.0);
					PathAngle=clamp_angle(PathAngle,-180);
					atm=PathAngle*4.0;
					if     (atm>0){atm+=10;}
					else if(atm<0){atm-=10;}
					atm=minmax(-200,atm,200);
					rms=minmax(100,-100+atm,-100);
					lms=minmax(100,-100-atm,-100);
				}
				drive(lms*rps_speed_percent/100.0,rms*rps_speed_percent/100.0);
			}
			else
			{
				rps_go=0;
				stop_driving();
				counter++; printf("Reached RPS waypoint[%i] at: %f/%f \n",counter, gx*tikmmfak,gy*tikmmfak);
			}
		}
		
		msleep(10);
	}
}

void rps_draw_table();
void rps_draw_targets();
void rps_draw_robot();
void rps_thread_drawing()
{
	while(1)
	{
		graphics_fill(white);
		
		rps_draw_table();
		rps_draw_targets();
		rps_draw_robot();
		
		graphics_update();
		msleep(100);
	}
}


//------------------------------------------DRAWING

void draw_line(int x1, int y1, int x2, int y2)
{graphics_line(mmtopx(x1),mmtopy(y1),mmtopx(x2),mmtopy(y2),black);}


void rps_draw_start()
{
	graphics_open(graph_size, graph_size);
	graphics_fill(white);
	graphics_update();
	
	
	draw_thread_id=thread_create(rps_thread_drawing);
	thread_start(draw_thread_id);
}

void rps_draw_stop()
{
	thread_destroy(draw_thread_id);
	graphics_close();
}

void rps_draw_robot()
{
	float dx=(float) (gx*tikmmfak*mmtop);
	float dy=(float) (gy*tikmmfak*mmtop);
	float da=ga;
	
	int point0_x=(float)             dx+rlp1*cosd(da);
	int point0_y=(float) graph_size-(dy+rlp1*sind(da));
	
	int point1_x=(float)             dx+rlp1*cosd(da)+rwp *sind(da);
	int point1_y=(float) graph_size-(dy-rwp *cosd(da)+rlp1*sind(da));
	
	int point2_x=(float)             dx+rlp1*cosd(da)-rwp *sind(da);
	int point2_y=(float) graph_size-(dy+rwp *cosd(da)+rlp1*sind(da));
	
	int point3_x=(float)             dx-rlp2*cosd(da)-rwp *sind(da);
	int point3_y=(float) graph_size-(dy+rwp *cosd(da)-rlp2*sind(da));
	
	int point4_x=(float)             dx-rlp2*cosd(da)+rwp *sind(da);
	int point4_y=(float) graph_size-(dy-rwp *cosd(da)-rlp2*sind(da));
	
	graphics_line(dx,graph_size-dy,point0_x,point0_y,black);
	graphics_line(dx,graph_size-dy,point3_x,point3_y,black);
	graphics_line(dx,graph_size-dy,point4_x,point4_y,black);
	graphics_line(point1_x,point1_y,point2_x,point2_y,black);
	graphics_line(point2_x,point2_y,point3_x,point3_y,black);
	graphics_line(point3_x,point3_y,point4_x,point4_y,black);
	graphics_line(point4_x,point4_y,point1_x,point1_y,black);
}

void rps_draw_targets()
{
	if(rps_go==1)
	{
		graphics_line(tiktopx(gx),tiktopy(gy),tiktopx(tgx),tiktopy(tgy),red);
		if(rps_drive_curve==1)
		{
			graphics_circle_fill(tiktopx(tcmgx),tiktopy(tcmgy),4,blue);
			graphics_circle_fill(tiktopx(tcgx ),tiktopy(tcgy ),4,red );
		}
	}
}


void rps_draw_table()
{
	//Pink
	graphics_circle(mmtopx(710),mmtopy( 720),mmtopx(80),black);
	graphics_circle(mmtopx(290),mmtopy(1680),mmtopx(80),black);
	
	graphics_rectangle_fill(mmtopx(1000),mmtopy(   0),mmtopx(1035),mmtopy(1020),black);
	graphics_rectangle_fill(mmtopx(1000),mmtopy(2400),mmtopx(1035),mmtopy(1380),black);
	
	graphics_rectangle_fill(mmtopx(   0),mmtopy( 390),mmtopx(1000),mmtopy( 440),pink);
	graphics_rectangle_fill(mmtopx(   0),mmtopy(2010),mmtopx(1000),mmtopy(1960),pink);
	
	graphics_rectangle_fill(mmtopx(1000),mmtopy(1020),mmtopx(1035),mmtopy(1380),pink);
	
	//Blue
	graphics_circle(mmtopx(1690),mmtopy(1680),mmtopx(80),black);
	graphics_circle(mmtopx(2100),mmtopy( 720),mmtopx(80),black);
	
	graphics_line(mmtopx(1400),mmtopy(   0),mmtopx(1400),mmtopy(1020),black);
	graphics_line(mmtopx(1400),mmtopy(2400),mmtopx(1400),mmtopy(1380),black);
	
	graphics_rectangle_fill(mmtopx(1400),mmtopy(   0),mmtopx(1365),mmtopy(1020),black);
	graphics_rectangle_fill(mmtopx(1400),mmtopy(2400),mmtopx(1365),mmtopy(1380),black);
	
	graphics_rectangle_fill(mmtopx(1400),mmtopy( 390),mmtopx(2400),mmtopy( 440),blue);
	graphics_rectangle_fill(mmtopx(1400),mmtopy(2010),mmtopx(2400),mmtopy(1960),blue);
	
	graphics_rectangle_fill(mmtopx(1400),mmtopy(1020),mmtopx(1365),mmtopy(1380),blue);
}


















































