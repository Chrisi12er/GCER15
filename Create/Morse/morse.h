#define moff 750		//morse sound on
#define mon 650			//morse sound off

#define unit 125
int wfm=0;
int gc_song_array[16][33];

void load_songs()
{
	
	create_write_byte(140);
	create_write_byte(0);
	create_write_byte(1);
	create_write_byte(69);
	create_write_byte(8);
	
	create_write_byte(140);
	create_write_byte(1);
	create_write_byte(1);
	create_write_byte(69);
	create_write_byte(24);	
}	

void start_morse()
{
	instant_servo(ccport, moff);
	load_songs();
}

void dot()
{
	printf(".");
	create_write_byte(141);
	create_write_byte(0);
	
//	instant_servo(ccport, mon);
	msleep(unit);
//	instant_servo(ccport, moff);
	
	msleep(unit);
}

void dash()
{
	printf("-");
	create_write_byte(141);
	create_write_byte(1);
	
	//instant_servo(ccport, mon);
	msleep(3*unit);
	//instant_servo(ccport, moff);
	
	msleep(unit);
}

void letter_end()
{
	printf(" ");
	msleep(2*unit);
}

void word_end()
{
	printf(" / ");
	msleep(6*unit);
}

void A()			//.-
{
	dot();
	dash();
	letter_end();
}
	
void B()			//-...
{
	dash();
	dot();
	dot();
	dot();
	letter_end();
}

void C()			//-.-.
{
	dash();
	dot();
	dash();
	dot();
	letter_end();
}
	
void D()			//-..
{
	dash();
	dot();
	dot();
	letter_end();
}
	
void E()			//.
{
	dot();
	letter_end();
}
	
void F()			//..-.
{
	dot();
	dot();
	dash();
	dot();
	letter_end();
}
	
void G()			//--.
{
	dash();
	dash();
	dot();
	letter_end();
}
	
void H()			//....
{
	dot();
	dot();
	dot();
	dot();	
	letter_end();
}
	
void I()			//..
{
	dot();
	dot();
	letter_end();
}
	
void J()			//.---
{
	dot();
	dash();
	dash();
	dash();
	letter_end();
}
	
void K()			//-.-
{
	dash();
	dot();
	dash();
	letter_end();
}
	
void L()			//.-..
{
	dot();
	dash();
	dot();
	dot();
	letter_end();
}
	
void M()			//--
{
	dash();
	dash();
	letter_end();
}
	
void N()			//-.
{
	dash();
	dot();
	letter_end();
}
	
void O()			//---
{
	dash();
	dash();
	dash();
	letter_end();
}
	
void P()			//.--.
{
	dot();
	dash();
	dash();
	dot();
	letter_end();
}
	
void Q()			//--.-
{
	dash();
	dash();
	dot();
	dash();
	letter_end();
}
	
void R()			//.-.
{
	dot();
	dash();
	dot();
	letter_end();
}
	
void S()			//...
{
	dot();
	dot();
	dot();
	letter_end();
}
	
void T()			//-
{
	dash();
	letter_end();
}
	
void U()			//..-
{
	dot();
	dot();
	dash();
	letter_end();
}
	
void V()			//...-
{
	dot();
	dot();
	dot();
	dash();
	letter_end();
}
	
void W()			//.--
{
	dot();
	dash();
	dash();
	letter_end();
}
	
void X()			//-..-
{
	dash();
	dot();
	dot();
	dash();
	letter_end();
}
	
void Y()			//-.--
{
	dash();
	dot();
	dash();
	dash();
	letter_end();
}
	
void Z()			//--..
{
	dash();
	dash();
	dot();
	dot();
	letter_end();
}

void morse(char string[],int loops)
{
	int l=0;
	
	while(l < loops)
	{
	
		int i=0;
		int letters = strlen(string);
		
		start_morse();
		
		while(i < letters)
		{
			if(string[i]=='A' || string[i]=='a')
			{
				A();
			}
			else if(string[i]=='B' || string[i]=='b')
			{
				B();
			}
			else if(string[i]=='C' || string[i]=='c')
			{
				C();
			}
			else if(string[i]=='D' || string[i]=='d')
			{
				D();
			}
			else if(string[i]=='E' || string[i]=='e')
			{
				E();
			}
			else if(string[i]=='F' || string[i]=='f')
			{
				F();
			}
			else if(string[i]=='G' || string[i]=='g')
			{
				G();
			}
			else if(string[i]=='H' || string[i]=='h')
			{
				H();
			}
			else if(string[i]=='I' || string[i]=='i')
			{
				I();
			}
			else if(string[i]=='J' || string[i]=='j')
			{
				J();
			}
			else if(string[i]=='K' || string[i]=='k')
			{
				K();
			}
			else if(string[i]=='L' || string[i]=='l')
			{
				L();
			}
			else if(string[i]=='M' || string[i]=='m')
			{
				M();
			}
			else if(string[i]=='N' || string[i]=='n')
			{
				N();
			}
			else if(string[i]=='O' || string[i]=='o')
			{
				O();
			}
			else if(string[i]=='P' || string[i]=='p')
			{
				P();
			}
			else if(string[i]=='Q' || string[i]=='q')
			{
				Q();
			}
			else if(string[i]=='R' || string[i]=='r')
			{
				R();
			}
			else if(string[i]=='S' || string[i]=='s')
			{
				S();
			}
			else if(string[i]=='T' || string[i]=='t')
			{
				T();
			}
			else if(string[i]=='U' || string[i]=='u')
			{
				U();
			}
			else if(string[i]=='V' || string[i]=='v')
			{
				V();
			}
			else if(string[i]=='W' || string[i]=='w')
			{
				W();
			}
			else if(string[i]=='X' || string[i]=='x')
			{
				X();
			}
			else if(string[i]=='Y' || string[i]=='y')
			{
				Y();
			}
			else if(string[i]=='Z' || string[i]=='z')
			{
				Z();
			}
			else if(string[i]==' ')
			{
				word_end();
			}
			else
			{
				printf("error");	
			}
			
			i++;
		}
		
		
		l++;
		
		printf("\n%s [%i/%i]\n", string, l, loops);
		msleep(2000);
	}
	wfm=0;
	
}

int loops;
char * word;
void morse_thread_helper()
{
	morse(word, loops);
}

void morse_thread(char string[], int tloops)
{
	word=string;
	loops=tloops;
	wfm=1;
	thread_start(thread_create(morse_thread_helper));
}

void wait_for_morse()
{
	while(wfm){msleep(100);}
}








































