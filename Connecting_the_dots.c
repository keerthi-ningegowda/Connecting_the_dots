///*OPENGL SOURCE CODE TO SIMULATE CONNECTION OF BOXES  */
/*BY KEERTHI.N  AND  ASHWITHA.G.BABU */
/*UNDER GUIDANCE OF PROF. VANI K.S. , PROF SUREKHA. K.B. AND PROF.NAGESHA A.G.*/

#include<stdio.h>     	
#include<unistd.h>	/*INCLUDING ALL THE REQUIRED HEADER FILES*/
#include<GL/glut.h>
#define MAXSIZE 20	//MAXIMUM ARRAYSSIZE IS 20

static GLfloat spin = 0.0;
int i,j;
float array[20][2];	//ARRAY TO STORE THE CO-ORDINATE POINTS TO LOCATE THE BOXES GIVEN BY THE USER
int cur=0;
int n;
int score;
char *str1="ALL THE POINTS ARE CONNECTED!!!!!";		//MESSAGE TO INDICATE THAT THE BOXES ARE CONNECTED		 
char *str2="POINTS ARE NOT CONNECTED!!!!!!";		//MESSAGE TO INDICATE THAT THE BOXES ARE NOT CONNECTED
char *str3="Click some points and then begin";		//ASKING THE USER TO CLICK SOME POINTS
char *str4="TERMINATING!!!";
char *c;
int res;
int count;

void spinDisplay(void)					//SPIN IDLE FUNCTION
{

	spin = spin + 0.2;				//INCREMENTING THE AXIS POINTS BY 0.2
	if(count == 2)					//STOP FOR 3rd ROUND
	{
		exit(0);
	}
	 if (spin > 360 )
	{	
		spin = spin - 360.0;
		glClear(GL_COLOR_BUFFER_BIT);
		count++;
	}
	glutPostRedisplay();
}


void display()						//DISPLAY FUNCTION FOR TERMINATION
{

	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	 glRasterPos2i(-20,45);
		for(c=str4;*c!='\0';c++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
			glFlush();
		}


	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0,0.0);			//POINTS REQUIRED FOR TERMINATING CONCENTRIC CIRCLES
	glColor3f(1.0,0.0,0.0);
	glVertex2f(2.0,2.0);
	glColor3f(1.0,1.0,0.0);
	glVertex2f(4.0,4.0);
	glColor3f(1.0,0.0,1.0);
	glVertex2f(6.0,6.0);
	glColor3f(1.0,0.0,0.5);
	glVertex2f(8.0,8.0);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}



void mail()		/*PROCEDURE TO SEND A MAIL TO THE SPECIFIED MAILBOX*/
{
	
		system("echo You tried to connect the points on `date` | mailx kirthi");
}




void drawpoints()	/*PROCEDURE TO DRAW THE POINTS USING ARRAY WHICH HAS THE POINTS OF POINTS SPECIFIED BY THE USER*/
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);		/*DRAWING THE RED COLOR POINTS*/
	glPointSize(10.0);
	for(i=0;i<n;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(array[i][0],array[i][1]);
		glEnd();
		glFlush();
	}	
}



void info() 		/*PROCEDURE TO DISPLAY THE CURRENT STATUS OF THE PROCESS*/
{
	if(n!=0)
	{
		res=n*10;
	}
	glRasterPos2f(100,40);		//INDICATING THE POSITION OF THE TEXT TO BE DISPLAYED
	glColor3f(1.0,1.0,1.0);	
	
	if(n==0)							
	{	
		for(c=str3;*c!='\0';c++)	/*CONDITIONAL CHECK BLOCK TO CHECK WHETHER POINTS ARE PRESENT OR NOT*/
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
			glFlush();
		}
			glClear(GL_COLOR_BUFFER_BIT);
			
	}


	if(score >= res && res !=0)		/*CONDITIONAL CHECK BLOCK TO CHECK WHETHER THE POINTS ARE CONNECTED OR NOT*/
	{
		for(c=str1;*c!='\0';c++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
			glFlush();
		}
			glClear(GL_COLOR_BUFFER_BIT);
	}



	if( score < res || score == 0)		/*CONDITIONAL CHECK BLOCK TO CHECK WHETHER THE POINTS ARE NOT CONNECTED*/
	{	
		for(c=str2;*c!='\0';c++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
			glFlush();
		}
			glClear(GL_COLOR_BUFFER_BIT);
	}
}
		
		

void drawlines()				/*PROCEDURE TO CONNECT THE POINTS*/
{
	if( n != 1)				//IF NUMBER OF POINTS IS NOT ONE CONTINUE
	{
		glColor3f(1.0,1.0,1.0);
		glLineWidth(2.0);
		for(i=0;i<n-1;i++)
		{
			j=i+1;
		score+=10;
			glBegin(GL_LINES);
			glVertex2f(array[i][0],array[i][1]);
			glVertex2f(array[j][0],array[j][1]);
			glEnd();
			glFlush();
		}
			glBegin(GL_LINES);
			glVertex2f(array[i][0],array[i][1]);
			glVertex2f(array[0][0],array[0][1]);
			glEnd();
			score+=10;
	}		glFlush();
	
}


void myinit()					/*CHANGING THE DEFAULT OPENGL COORDINATE SYSTEM*/
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(0.0,500.0,0.0,500.0);
}



void mymouse(int btn,int state,int x,int y)	/*MYMOUSE PROCEDURE TO WORK WITH MOUSE BUTTONS*/
{

	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)	/*IF RIGHT BUTTON OF MOUSE IS CLICKED TERMINATE FROM THE PROGRAM*/
	{
			
		glClear(GL_COLOR_BUFFER_BIT);
		
		glFlush();
		glEnable(GL_DOUBLE);
		glutDisplayFunc(display);
		glutIdleFunc(spinDisplay);
	}

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)	/*IF LEFT BUTTON OF MOUSE IS CLICKED THEN GET THE COREESPONDING CO_ORDINATES   AND STORE IT IN THE ARRAY*/
	{
		if(cur<=MAXSIZE)
		{
			n++;		
			array[cur][0]=x;
			array[cur][1]=y;
			cur++;
		}
		
		
	}
}



void mykey(unsigned char key,int x,int y)	/*MYKEY PROCEDURE TO WORK WITH SPECIFIC KEYS PRESSED BY THE USER*/
{
	if(key == 'p')				/*IF 'p' IS PRESSED DRAW THE POINTS*/
		drawpoints();		
	
	if(key == 'l')			/*IF 'l' IS PRESSED THE POINTSS ARE CONNECTED*/
		drawlines();

	if(key == 'i')				/*IF 'i' IS PRESSED THEN CURRENT STATUS IS OBTAINED*/
		info();

	if(key == 'm')				/*IF 'm' IS PRESSED THEN MAIL IS THROWN TO THE SPECIFIED  MAILBOX*/
		mail();

}



void myreshape(int w,int h)			/*TO CHANGE THE SIZE OF APPLICATION WINDOW*/
{
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();
	glOrtho(0,w,h,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}





int main(int argc,char **argv)			/*MAIN FUNCTION*/
{
	
	printf("\n********GREETINGS**********\n");
	printf("\n   CONNECTING THE POINTS  \n");
	printf("\n**********INSTRUCTIONS**********\n");
	printf("\n     MOUSE COMMANDS     \n");
	printf("\n1.LEFT BUTTON TO GET THE POINTS(POINTS SHOULD BE LESS THAN 20)\n");
	printf("\n2.RIGHT BUTTON TO TERMINATE\n");
	printf("\n    KEYBOARD COMMANDS   \n");
	printf("\nKEY p TO DRAW THE POINTS\n");
	printf("\nKEY l TO DRAW THE LINES TO CONNECT THE POINTS\n");
	printf("\nKEY i TO GET THE INFO \n");
	printf("\nKEY m TO MAIL THE TIME AT WHICH THE PROGRAM WAS RUN\n");
	glutInit(&argc,argv);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(0,0);
	glutCreateWindow("dots");
	glutReshapeFunc(myreshape);
	glEnable(GL_LINE_SMOOTH);		//ANTI-ALIASING (SYSTEM DEPENDENT)
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);	//ANTI-ALIASING (SYSTEM DEPENDENT)
	myinit();
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykey);		//KEYBOARD CALLBACK FUNCTION
	glutMainLoop();				//TO CAUSE THE PROGRAM ENTER INTO EVENT PROCESSING LOOP
	return 0;
}					
	

