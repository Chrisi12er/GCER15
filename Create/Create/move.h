#define pi 3.14159
#define diam 262		//262


float corr_d[11];
float corr_t[11];
void set_cor()
{
corr_d[ 0]=0;	//  0
corr_d[ 1]=-3;	// 50
corr_d[ 2]=0;	//100		35
corr_d[ 3]=16;	//150
corr_d[ 4]=5;	//200
corr_d[ 5]=-7;	//250
corr_d[ 6]=-11;	//300
corr_d[ 7]=-31;	//350
corr_d[ 8]=-80;	//400
corr_d[ 9]=-60;	//450
corr_d[10]=-11;	//500

//adjusted for 90 degrees
	
corr_t[ 0]=0;	//  0
corr_t[ 1]=-5;	// 50
corr_t[ 2]=0;	//100	1 Grad zu kurz
corr_t[ 3]=-8;	//150
corr_t[ 4]=-12;	//200	5 Grad zu viel -15
corr_t[ 5]=-20;	//250
corr_t[ 6]=-25;	//300	10 Grad zu viel
corr_t[ 7]=-40;	//350
corr_t[ 8]=-50;	//400
corr_t[ 9]=-35;	//450
corr_t[10]=-50;	//500	
}

void drive(float speed, float dist)
{
	dist+=corr_d[(int) speed/50];
	
	float wait=(float) ((dist*1000)/speed);
	if(dist>0){create_drive_straight( speed);}
	if(dist<0){create_drive_straight(-speed);}
	if(wait<0){wait*=-1;}
	msleep(wait);
	create_stop();
}

/*void straight(float speed, float distance)
{
	float used_corr=corr[(int) speed/50)];
	float velocity=speed+(200.0-speed)/10.0;
	create_drive_straight(velocity);
}
*/
void turn (float speed, float angle)
{
	//float diam=262;		//262 wheel distance
	
	//diam+=corr_t[(int) speed/50];
	
	
	float dist=(diam*pi)/(360/angle);
	
	dist+=(corr_t[(int) speed/50]);
	
	float wait=(float) ((dist*1000)/speed);
	if(angle>0){create_spin_CW(speed);}
	if(angle<0){create_spin_CCW(speed);}
	if(wait<0){wait*=-1;}
	msleep(wait);
	create_stop();	
}

