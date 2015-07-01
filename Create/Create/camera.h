// Created on Do März 12 2015

// Replace FILE with your file's name
#ifndef _camera_H_
#define _camera_H_

#define greenchannel 0
#define redchannel 1
#define goldchannel 2

#define blobsize 500
#define blobsizepom 250

int botguycolor=-1;

int getarea(int channel)
{
	if(get_object_count(channel) > 0)
	{
		return get_object_area(channel, 0);
	}
	else 
	{
		return 0;
	}		
}

int camerachecks;
int color_found=0;

void findbotguycolor()
{
	camerachecks=0;
	while(botguycolor!=0 && botguycolor!=1 && camerachecks <50)
	{	
	
		camera_update();
		camera_update();
		camera_update();
		camera_update();
		camera_update();
	
		if(getarea(greenchannel) > blobsize)
		{
			drive(100,-100);
			movearm(topheight-5);
			claw(cgreenguy);
			botguycolor=greenchannel;
			color_found=1;
		}
	
		else if(getarea(redchannel) > blobsize)
		{
			//turn(50,5);
			drive(50,-130);
			movearm(topheight);
			printf("[%f]\n",seconds());
			mrp(motarmport,-200,-300);
			//bmd(motarmport);
			printf("[%f]",seconds());
			claw(credguy);
			botguycolor=redchannel;
			color_found=1;
		}
		
		else
		{
			camerachecks++;
			printf("Error finding Botguy Color #%d [%f]\n", camerachecks, seconds());
			msleep(50);
		}
	
	}
}

void findgoldpom ()
{
	int speed;
	
	while(1)
	{
		camera_update();
		camera_update();
		camera_update();
		camera_update();
		camera_update();
		
		
		if(getarea(goldchannel) > blobsizepom)
		{
					
			if (get_object_center_column(goldchannel,0) >= 75 && get_object_center_column(goldchannel,0) <= 85)
			{
				break;
			}
			
			speed=(get_object_center_column(goldchannel,0)-80)*1;
			
			create_drive_direct(speed,-speed);
			
		}
		
		else
		{
			create_spin_CW(50);
		}
		
		msleep(10);
	}
	
	create_stop();
}

int spinvalue=0;

void findredguy ()
{
	int speed;
	
	
	while(1)
	{
		camera_update();
		camera_update();
		camera_update();
		camera_update();
		camera_update();
		
		
		if(getarea(redchannel) > blobsize)
		{
					
			if (get_object_center_column(redchannel,0) >= 75 && get_object_center_column(redchannel,0) <= 85)
			{
				break;
			}
			
			speed=(get_object_center_column(redchannel,0)-80)*1;
			
			create_drive_direct(speed,-speed);
			
		}
		
		else
		{
			create_spin_CW(50);
			spinvalue+=50;
		}
		
		msleep(10);
	}
	
	create_stop();
}



#endif
