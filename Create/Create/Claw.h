
#define motarmport 1	//motor port for arm
#define motclawport 0	//motor port for claw
#define potiport 0		//sensor port for poti
#define fbarm 0			//servo for frisbee arm
#define fbclaw 1		//servo for frisbee claw
#define ccport 2		//servo for cable carrier

#define ccup 1300		//cable carrier up
#define ccmiddle 900	//cable carrier middle
#define ccdown 620		//cable carrier down

#define hat0   0.0		//height at poti value 0
#define hat1  90.0		//height at poti value 150
#define hat2 290.0		//height at poti value 873
#define hat3 430.0		//height at poti value 1023

#define slim0 150.0
#define slim1 873.0

#define copen 0
#define cclosed 1
#define credguy 2
#define cgreenguy 3
#define ctwocubes 4
#define conecube 5

#define lightport 1

#define startheight 170
#define boardheight 415
#define topheight 430

//start position bei 160mm

int wfc;
int wfa;

float starting_time;
float get_time()
{return seconds()-starting_time;}

float GetClawHeight()
{
	float ret;
	float temp=(float)analog(potiport);
		 if(temp<slim0){ret=hat0+(hat1-hat0)*(temp      )/(       slim0);}
	else if(temp<slim1){ret=hat1+(hat2-hat1)*(temp-slim0)/(slim1 -slim0);}
	else               {ret=hat2+(hat3-hat2)*(temp-slim1)/(1023.0-slim1);}
	return ret;
}


void movearm(float theight)
{

	if(theight>GetClawHeight())
	{
		motor(motarmport,100);
		while(theight>GetClawHeight())
		{msleep(10);}
		
		mrp(motarmport,1000,0);
		//motor(motarmport,0);
	}

	else if(theight == 5)
	{
		motor(motarmport,-50);
		while(theight<=GetClawHeight())
		{msleep(10);}
		
		mrp(motarmport,1000,-50);
	}
	
	else
	{
		motor(motarmport,-50);
		while(theight<=GetClawHeight())
		{msleep(10);}
		
		mrp(motarmport,1000,0);
		//bmd(motarmport);
		//motor(motarmport,0);
	}
	wfa=0;
}



void claw_h(int position)
{
	if (position==0)					//open 120mm 0
	{
		mtp(motclawport,1000,4000);
		printf("Claw open\n");
	}
	else if (position==1)				//closed 30mm 3500
	{
		mtp(motclawport,1000,0);
		printf("Claw closed\n");
	}
	else if (position==2)				//botguy red 45mm 3000
	{
		mtp(motclawport,1000,1000);
		printf("Claw Botguy red\n");
	}
	else if (position==3)				//botguy green 60mm 2400
	{
		mtp(motclawport,1000,1400);
		printf("Claw Botguy green\n");
	}
	else if (position==4)				//two cubes 90mm 1200
	{
		mtp(motclawport,1000,2600);
		printf("Claw Two Cubes\n");
	}
	else if (position==5)				//one cube 30mm 3500
	{
		mtp(motclawport,1000,500);
		printf("Claw One Cube\n");
	}
	else
	{
		printf("Error Claw\n");
	}
	
}

void claw(int position)
{
	claw_h(position);
	bmd(motclawport);
}

void claw_thread(int position)
{
	claw_h(position);
}

void wait_for_claw()
{
	bmd(motclawport);
}


/*
int ctpos;
void claw_thread_helper()
{
	claw(ctpos);
}

void claw_thread(int position)
{
	ctpos=position;
	wfc=1;
	thread_start(thread_create(claw_thread_helper));
}

void wait_for_claw()
{
	while(wfc){msleep(100);}
}
*/

int mtheight;
void movearm_thread_helper()
{
	movearm(mtheight);
}

void movearm_thread(int theight)
{
	mtheight=theight;
	wfa=1;
	thread_start(thread_create(movearm_thread_helper));
}

void wait_for_arm()
{
	while(wfa){msleep(100);}
}


void slowservo(int servoport, int servoposition)
{
	if (servoposition > get_servo_position(servoport))
	{
		while(get_servo_position(servoport) < servoposition)
		{
			set_servo_position(servoport,(get_servo_position(servoport)+5));
			msleep(10);
		}
	}
	
	else	//if servoposition < get_servo_position
	{
		while(get_servo_position(servoport) > servoposition)
		{
			set_servo_position(servoport,(get_servo_position(servoport)-5));
			msleep(10);
		}
	}
	
}

int sp[4];

void instant_servo(int id ,int target)
{
	set_servo_position(id,target);
	sp[id]=target;
}


void smooth_servo(int id ,int target , double time)
{
	if(time>0.0)
	{
		int    p=sp[id];
		int    d=target-p;
		
		double t=seconds();
		
		while(seconds()<t+time)
		{
			instant_servo(id, p+(int)( (double)d*(seconds()-t)/time));
			msleep(10);
		}
	}
	
	instant_servo(id, target);
}
