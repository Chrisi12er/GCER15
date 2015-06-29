
#define degradfak 0.01745329


float sind(float a)
{
	return sin(a*degradfak);
}

float asind(float a)
{
	return asin(a)/degradfak;
}

float cosd(float a)
{
	return cos(a*degradfak);
}

float acosd(float a)
{
	return (acos(a)/degradfak);
}

float tand(float a)
{
	return tan(a*degradfak);
}

float atand2(float yy,float xx)
{
	return (atan2(yy,xx)/degradfak);
}

float sqr(float a)
{
	return pow(a,2);
}

float pytag(float xx,float yy)
{
	return sqrt(sqr(xx)+sqr(yy));
}

int range_rand(int min, int max)
{
	return ((rand()%(max-min))+min);
}

float max(float a, float b)
{
	float ret;
	if(a>b){ret=a;}
	else   {ret=b;}
	return ret;
}

float min(float a, float b)
{
	float ret;
	if(a<b){ret=a;}
	else   {ret=b;}
	return ret;
}

float minmax(float a, float b, float c)
{
	float ret;
	if(a>c){ret=min(max(c,b),a);}
	else   {ret=min(max(a,b),c);}
	return ret;
}

float pos(float a)
{
	if(a<0){a=-a;}
	return a;
}

void rotate_point(float *px, float *py, float cx, float cy, float ca)
{
	float dx=*px-cx;
	float dy=*py-cy;
	
	*px=cx+(dx*cosd(ca)-dy*sind(ca));
	*py=cy+(dy*cosd(ca)+dx*sind(ca));
}


float clamp_angle(float angle ,float min)
{
	
	while(angle<min    ){angle+=360;}
	while(angle>min+360){angle-=360;}
	return angle;
	
}


float calc_radius(int sx, int sy, float an, int tx, int ty)
{
	float xd=(tx-sx)*cosd(an-90.0)-(ty-sy)*sind(an-90.0);
	float yd=(tx-sx)*sind(an-90.0)+(ty-sy)*cosd(an-90.0);
	if(xd!=0.0){printf("%f\n",(xd*xd+yd*yd)/(2*xd)); return ((xd*xd+yd*yd)/(2.0*xd));}
	else{return 0.0;}
}

float calc_radius_point(int sx, int sy, float an, int tx, int ty, float *mx, float *my)
{
	float radius=calc_radius(sx,sy,an,tx,ty);
	*mx=sx+radius*cosd(an-90.0);
	*my=sy+radius*sind(an-90.0);
	
	return radius;
}


int calc_side_of_point(int sx, int sy, float an, int tx, int ty)
{
	float xx=(tx-sx)*cosd(an-90.0)-(ty-sy)*sind(an-90.0);
	if(xx>0.0){return 1;} else {return -1;}
}


































