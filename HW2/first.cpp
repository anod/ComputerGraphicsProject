// OpenGL
#include "glut.h"
#include <math.h>
#include <time.h>

#define PI 3.14
const int GSIZE = 200;

double grid[GSIZE][GSIZE]={0};

double angle=PI,dangle=0.0,start=0;
double eyex=1,eyey=10,eyez=20;
double dx=0,dy=0,dz=0;
double sightx=0,sighty= -0.2,sightz = -1;
double speed = 0;
double planex=0,planey=8,planez=15;
double plane_angle=PI/2,plane_speed=0,plane_ang_speed=0;
double pitch = 0;
bool IsBuilding = false;


void Smooth();
void UpdateTerrain1();
void UpdateTerrain2();
void UpdateTerrain3();

void init()
{
	int i;
	glClearColor(0.4,0.4,0.4,0); // set background color
	glEnable(GL_DEPTH_TEST);

	srand((unsigned)time(NULL));

	for(i=1;i<200;i++)
		UpdateTerrain3();
	for(i=1;i<400;i++)
		UpdateTerrain1();
	for(i=1;i<50;i++)
		UpdateTerrain2();
	Smooth();
	for(i=1;i<5;i++)
		UpdateTerrain2();

}

// low-pass filter
void Smooth()
{
	double tmp[GSIZE][GSIZE] = {0};
	int i,j;
	for(i=1;i<GSIZE-1;i++)
		for(j=1;j<GSIZE-1;j++)
		{
			tmp[i][j] = (grid[i-1][j-1] + grid[i-1][j] +grid[i-1][j+1] +
				grid[i][j-1] + 4*grid[i][j] +grid[i][j+1]+
				grid[i+1][j-1] + grid[i+1][j] +grid[i+1][j+1])/12;
		}

	for(i=1;i<GSIZE-1;i++)
		for(j=1;j<GSIZE-1;j++)
			grid[i][j] = tmp[i][j];
}

void UpdateTerrain1()
{
	double a,b,delta = 0.1;
	int x1,x2,y1,y2,x,y;

	x1 = rand()% GSIZE;
	y1 = rand()% GSIZE;
	x2 = rand()% GSIZE;
	y2 = rand()% GSIZE;

	if(rand()%2==0) delta = -delta;

	if(x1!=x2)
	{
		a = (y2-y1)/(double)(x2-x1) ;
		b = y1 - a*x1;
		for(y=0;y<GSIZE;y++)
			for(x=0;x<GSIZE;x++)
			{
				if(y>a*x+b) grid[y][x]+=delta;
				else grid[y][x] -= delta;
			}
	}
}

void UpdateTerrain2()
{
	int x1,y1,points = 1500,direction;
	double delta = 0.1;
	x1 = rand()% GSIZE;
	y1 = rand()% GSIZE;
	if(rand()%2==0) delta = -delta;

	while(points>0)
	{
		grid[y1][x1] += delta;
		direction = rand()%4;
		switch(direction)
		{
		case 0: // up
			y1--;
			break;
		case 1: // right
			x1++;
			break;
		case 2: // down
			y1++;
			break;
		case 3: // left
			x1--;
			break;
		} 
		x1 = (x1+GSIZE) % GSIZE;
		y1 = (y1+GSIZE) % GSIZE;
		points--;
	}
}

void UpdateTerrain3()
{
	int x,y,r;
	int i,j;
	double dist,alpha;
	double delta = 1;

	x = rand()% GSIZE;
	y = rand()% GSIZE;
	r = 1 +rand()%30 ;
	if(rand()%2==0) delta = -delta;

	for(i=y-r;i<=y+r;i++)
		for(j = x-r;j<=x+r;j++)
		{
			if(i>=0 && j>=0 && i<GSIZE && j<GSIZE)
			{
				dist = sqrt(((double)x-j)*(x-j) + (i-y)*(i-y));
				if(dist<r)
				{
					alpha = acos(dist/r);
					grid[i][j] += delta * 0.03* r*sin(alpha);
				}
			}
		}


}

void SetColor(double h)
{
	if(h>-5)
	{
	h=fabs(h);
//	glColor3d((h+3)/10,(h+3)/10,(h+3)/6);
	if(h>0 && h<0.4) // sand
		glColor3d(0.8,0.8,0.5);
	else if(h<5)
		glColor3d(0.2+h/30,(5-h)/6,0);
	else glColor3d(h/11,h/11,h/10);
	}
	else glColor3d(0,0,0);
}

void DrawFloor()
{
	int i,j;

	for(i=1;i<GSIZE;i++)
		for(j=1;j<GSIZE;j++)
		{
//			glBegin(GL_LINE_LOOP);
			glBegin(GL_POLYGON);
					SetColor(grid[i][j]);
				glVertex3d(j-GSIZE/2,grid[i][j],i-GSIZE/2);
					SetColor(grid[i][j-1]);
				glVertex3d(j-1-GSIZE/2,grid[i][j-1],i-GSIZE/2);
					SetColor(grid[i-1][j-1]);
				glVertex3d(j-1-GSIZE/2,grid[i-1][j-1],i-1-GSIZE/2);
					SetColor(grid[i-1][j]);
				glVertex3d(j-GSIZE/2,grid[i-1][j],i-1-GSIZE/2);
			glEnd();
		}

// water
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0,0,0.5,0.7);
	glBegin(GL_POLYGON);
			glVertex3d(-GSIZE/2,0,-GSIZE/2);
			glVertex3d(GSIZE/2,0,-GSIZE/2);
			glVertex3d(GSIZE/2,0,GSIZE/2);
			glVertex3d(-GSIZE/2,0,GSIZE/2);
	glEnd();
	glDisable(GL_BLEND);


/*	
	glColor3d(0,1,0);
	for(i=1;i<GSIZE;i++)
		for(j=1;j<GSIZE;j++)
		{
			glBegin(GL_LINE_LOOP);
				glVertex3d(j-GSIZE/2,1+grid[i][j],i-GSIZE/2);
				glVertex3d(j-1-GSIZE/2,1+grid[i][j-1],i-GSIZE/2);
				glVertex3d(j-1-GSIZE/2,1+grid[i-1][j-1],i-1-GSIZE/2);
				glVertex3d(j-GSIZE/2,1+grid[i-1][j],i-1-GSIZE/2);
			glEnd();
		}
		*/
}

void DrawPlane()
{
	// front
	glColor3d(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex3d(2.3,0.3,0);
		glVertex3d(1.5,0.3,0.4);
		glVertex3d(1.5,0.5,0);
	glEnd();
	glColor3d(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex3d(2.3,0.3,0);
		glVertex3d(1.5,0.3,-0.4);
		glVertex3d(1.5,0.5,0);
	glEnd();

	glBegin(GL_POLYGON);
			glColor3d(1,1,1);
		glVertex3d(3.2,0,0);
			glColor3d(0.7,0.7,0.7);
		glVertex3d(1.5,0,0.5);
			glColor3d(0.6,0.6,0.6);
		glVertex3d(1.5,0.3,0.4);
		glVertex3d(2.3,0.3,0);
	glEnd();
	glBegin(GL_POLYGON);
			glColor3d(1,1,1);
		glVertex3d(3.2,0,0);
			glColor3d(0.7,0.7,0.7);
		glVertex3d(1.5,0,-0.5);
			glColor3d(0.6,0.6,0.6);
		glVertex3d(1.5,0.3,-0.4);
		glVertex3d(2.3,0.3,0);
	glEnd();
	// middle
	glBegin(GL_POLYGON);
			glColor3d(0.7,0.7,0.7);
		glVertex3d(1.5,0,0.5);
			glColor3d(0.8,0.8,0.8);
		glVertex3d(1.5,0.3,0.4);
			glColor3d(0.5,0.5,0.5);
		glVertex3d(-3.5,0,0);
	glEnd();

	glBegin(GL_POLYGON);
			glColor3d(0.8,0.8,0.8);
		glVertex3d(1.5,0.3,0.4);
			glColor3d(0.5,0.5,0.8);
		glVertex3d(1.5,0.5,0);
			glVertex3d(-3.5,0,0);
	glEnd();

	glBegin(GL_POLYGON);
			glColor3d(0.7,0.7,0.7);
		glVertex3d(1.5,0,-0.5);
			glColor3d(0.8,0.8,0.8);
		glVertex3d(1.5,0.3,-0.4);
			glColor3d(0.5,0.5,0.5);
		glVertex3d(-3.5,0,0);
	glEnd();

	glBegin(GL_POLYGON);
			glColor3d(0.8,0.8,0.8);
		glVertex3d(1.5,0.3,-0.4);
			glColor3d(0.5,0.5,0.8);
		glVertex3d(1.5,0.5,0);
			glVertex3d(-3.5,0,0);
	glEnd();
	// wings
	glBegin(GL_POLYGON);
			glColor3d(0.6,0.6,0.6);
		glVertex3d(1.5,0.2,0);
		glVertex3d(-0.5,0.2,2.5);
		glVertex3d(-1,0.2,2.5);
		glVertex3d(-0.5,0.1,0);
	glEnd();
	glBegin(GL_POLYGON);
			glColor3d(0.6,0.6,0.6);
		glVertex3d(1.5,0.2,0);
		glVertex3d(-0.5,0.2,-2.5);
		glVertex3d(-1,0.2,-2.5);
		glVertex3d(-0.5,0.1,0);
	glEnd();
	// back

	glBegin(GL_POLYGON);
			glColor3d(0.6,0.6,0.6);
		glVertex3d(-1,0,0);
			glColor3d(0.6,0.6,1);
		glVertex3d(-3.3,1,0);
		glVertex3d(-3.6,1,0);
			glColor3d(0.6,0.6,0.6);
		glVertex3d(-3.2,0,0);
	glEnd();
	// back wings
	glBegin(GL_POLYGON);
			glColor3d(0.6,0.6,0.6);
		glVertex3d(-1.5,0,0);
		glVertex3d(-2.5,0,1);
		glVertex3d(-2.7,0,1);
		glVertex3d(-2.7,0,-1);
		glVertex3d(-2.5,0,-1);
	glEnd();

	

}

void display()
{
	// fill the buffer with the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,600,600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(eyex,eyey,eyez,eyex+sightx,eyey+sighty,eyez+sightz,0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawFloor();
	// plane
	glTranslated(planex,planey, planez);
	glRotated(plane_angle*180/PI,0,1,0);  // yaw
	glRotated(-plane_ang_speed*2000,1,0,0); // roll
	glRotated(pitch*180/PI,0,0,1);
	DrawPlane();

	glutSwapBuffers();
}

void displayComb()
{
	// fill the buffer with the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,300,300,300);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(eyex,eyey,eyez,eyex+sightx,eyey+sighty,eyez+sightz,0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawFloor();
	// plane
	glPushMatrix();
		glTranslated(planex,planey, planez);
		glRotated(plane_angle*180/PI,0,1,0);  // yaw
		glRotated(-plane_ang_speed*2000,1,0,0); // roll
		glRotated(pitch*180/PI,0,0,1);
		DrawPlane();
	glPopMatrix();

// top view
	glViewport(300,300,300,300);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(eyex,80,eyez,eyex,0,eyez,sightx,0,sightz);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawFloor();
	// plane
	glPushMatrix();
	glTranslated(planex,planey, planez);
	glRotated(plane_angle*180/PI,0,1,0);  // yaw
	glRotated(-plane_ang_speed*2000,1,0,0); // roll
	glRotated(pitch*180/PI,0,0,1);
	DrawPlane();
	glPopMatrix();

	// cockpit view
	glViewport(0,0,600,300);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(planex+2*sin(plane_angle+PI/2),
		planey+2*sin(pitch),planez+2*cos(plane_angle+PI/2),
		planex+3*sin(plane_angle+PI/2),
		planey+3*sin(pitch),planez+3*cos(plane_angle+PI/2),
		0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawFloor();
	// plane
	glPushMatrix();
		glTranslated(planex,planey, planez);
		glRotated(plane_angle*180/PI,0,1,0);  // yaw
		glRotated(-plane_ang_speed*2000,1,0,0); // roll
		glRotated(pitch*180/PI,0,0,1);
		DrawPlane();
	glPopMatrix();

	glutSwapBuffers();
}

void displayTop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,600,600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(eyex,80,eyez,eyex,0,eyez,sightx,0,sightz);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawFloor();
	// plane
	glPushMatrix();
	glTranslated(planex,planey, planez);
	glRotated(plane_angle*180/PI,0,1,0);  // yaw
	glRotated(-plane_ang_speed*2000,1,0,0); // roll
	glRotated(pitch*180/PI,0,0,1);
	DrawPlane();
	glPopMatrix();

	glutSwapBuffers();
}

void displayCockpit()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(planex+2*sin(plane_angle+PI/2),
		planey+2*sin(pitch),planez+2*cos(plane_angle+PI/2),
		planex+3*sin(plane_angle+PI/2),
		planey+3*sin(pitch),planez+3*cos(plane_angle+PI/2),
		0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DrawFloor();
	// plane
	glPushMatrix();
		glTranslated(planex,planey, planez);
		glRotated(plane_angle*180/PI,0,1,0);  // yaw
		glRotated(-plane_ang_speed*2000,1,0,0); // roll
		glRotated(pitch*180/PI,0,0,1);
		DrawPlane();
	glPopMatrix();

	glutSwapBuffers();
}

void idle()
{
	int i,j;
	double r;
	angle+=dangle;
	start+=0.4;
	sightx = sin(angle);
	sightz = cos(angle);
	eyex+=sightx*speed;
	eyey+=dy;
	eyez+=sightz*speed;

	// plane
	plane_angle+=plane_ang_speed;
	planex+=plane_speed*sin(plane_angle+PI/2);
	planez+=plane_speed*cos(plane_angle+PI/2);
	planey+=plane_speed*sin(pitch);

/*	if(IsBuilding)
	{
		UpdateTerrain1();
		UpdateTerrain2();
		UpdateTerrain3();
	}
	*/
/*	start-=0.03;

for(i=0;i<GSIZE;i++)
		for(j=0;j<GSIZE;j++)
		{
			r = sqrt( (i-GSIZE/2.0)*(i-GSIZE/2) + (j-GSIZE/2)*(j-GSIZE/2) );
			grid[i][j] = 3*sin(start+ r/6.0) ;
		}
*/
	glutPostRedisplay();
}


void mouse(int button,int state,int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		IsBuilding = !IsBuilding;
	else 	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
		Smooth();

}

void SpecialKey(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		dangle+=0.001;
		break;
	case GLUT_KEY_RIGHT:
		dangle-=0.001;
		break;
	case GLUT_KEY_UP:
		speed+=0.01;
		break;
	case GLUT_KEY_DOWN:
		speed-=0.01;
		break;
	case GLUT_KEY_PAGE_UP:
		dy+=0.01;
		break;
	case GLUT_KEY_PAGE_DOWN:
		dy-=0.01;
		break;
		
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	switch( key)
	{
	case 'a': // left
			plane_ang_speed+=0.002;
		break;
	case 'd':  // right
			plane_ang_speed-=0.002;
		break;
	case 'w':  // forward
			plane_speed+=0.01;
		break;
	case 's':   // backward
			plane_speed-=0.01;
		break;
	case 'r':   // up
			pitch+=0.02;
		break;
	case 'f':   // down
			pitch-=0.02;
		break;
	}
}

void menu(int option)
{
	switch(option)
	{
	case 1:
		glutDisplayFunc(display);
		break;
	case 2:
		glutDisplayFunc(displayComb);
		break;
	case 3:
		glutDisplayFunc(displayTop);
		break;
	case 4:
		glutDisplayFunc(displayCockpit);
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D Example");

	// onPaint
	glutDisplayFunc(displayComb);
	// onTimer
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(Keyboard);

	glutCreateMenu(menu);
	glutAddMenuEntry("Regular View",1);
	glutAddMenuEntry("Combined View",2);
	glutAddMenuEntry("Top View",3);
	glutAddMenuEntry("Cockpit View",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutMainLoop();
}