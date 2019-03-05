

#define OPENGLUT_STATIC
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "GLAUX.h"

#pragma comment ( lib, "glaux.lib" )
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


GLuint	texture[26];

GLuint textemp[3] = { 0,0,0 };
GLuint textempsky[6] = { 0,0,0,0,0,0 };

GLuint texTV, texSky;

bool doorFlag = true;


GLuint drawcube;
GLfloat updown, angle = 0, rud = 0, pro_up_down = 47.0;
static GLfloat sx = 0, sy = 0, sz = 0;
static int lflag = GL_TRUE, rflag = GL_TRUE;
static GLuint j = 0, k = 0;
AUX_RGBImageRec* LoadBMP(char* filename)

{

	FILE* file = NULL;



	if (!filename)

	{

		return NULL;

	}



	file = fopen(filename, "r");



	if (file)

	{

		fclose(file);

		return auxDIBImageLoad(filename);

	}

	return NULL;

}



int LoadGLTextures()

{

	int status = FALSE;

	AUX_RGBImageRec* textureImage[26];

	memset(textureImage, 0, sizeof(AUX_RGBImageRec*) * 26);

	char* texImg[26] = { (char*)"data\\front.bmp",(char*)"data\\back.bmp",(char*)"data\\top.bmp",

			(char*)"data\\bottom.bmp",(char*)"data\\right.bmp",(char*)"data\\left.bmp",(char*)"data\\shazi.bmp",(char*)"data\\qiang.bmp",
			(char*)"data\\bizhi.bmp",(char*)"data\\Door.bmp",(char*)"data\\diban1.bmp",(char*)"data\\airconditionfront.bmp",
			(char*)"data\\airconditionback.bmp",(char*)"data\\dianshi.bmp",(char*)"data\\zhuomian.bmp",(char*)"data\\chenge.bmp",
			(char*)"data\\kirisaki.bmp",(char*)"data\\xinyiji.bmp",(char*)"data\\ft.bmp",(char*)"data\\bk.bmp",(char*)"data\\uup.bmp",
			(char*)"data\\dn.bmp",(char*)"data\\rt.bmp",(char*)"data\\lf.bmp",(char*)"data\\fangding.bmp",(char*)"data\\chuanghu.bmp" };



	for (int i = 0; i < 26; i++)

	{

		if (textureImage[i] = LoadBMP(texImg[i]))

		{

			status = TRUE;

			glGenTextures(1, &texture[i]);

			glBindTexture(GL_TEXTURE_2D, texture[i]);

			glTexImage2D(GL_TEXTURE_2D, 0, 4, textureImage[i]->sizeX, textureImage[i]->sizeY,

				0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[i]->data);



			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}



		if (textureImage[i])

		{

			if (textureImage[i]->data)

			{

				free(textureImage[i]->data);

			}
			glBindTexture(GL_TEXTURE_2D, 0);
			free(textureImage[i]);

		}

	}



	return status;

}


void reshape(int w/*屏幕的宽*/, int h/*屏幕的高*/)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//设置GL窗口大小
	glMatrixMode(GL_PROJECTION);//将当前矩阵指定为投影矩阵
	glLoadIdentity();//获取单位矩阵
	gluPerspective(90, w / h, 0.5, 2000);//形成透视效果
	glMatrixMode(GL_MODELVIEW);//将当前矩阵指定为观察矩阵
	glLoadIdentity();//获取单位矩阵
	gluLookAt(-30, 30, 70, 0, 0, 0, 0, 10, 0);//设置观察点
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//画出正方体显示列表
	drawcube = glGenLists(1);
	glNewList(drawcube, GL_COMPILE);
	glutSolidCube(1);
	glEndList();

	//设置普通灯光照0位置及参数；
	GLfloat AmbientLight[4] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glEnable(GL_LIGHT0);      //允许0#灯使用


	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);


}
int InitGL(GLvoid)

{

	if (!LoadGLTextures())

	{
		return FALSE;
	}

	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDisable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	texTV = texture[17];
	textempsky[0] = texture[0];
	textempsky[1] = texture[1];
	textempsky[2] = texture[2];
	textempsky[3] = texture[3];
	textempsky[4] = texture[4];
	textempsky[5] = texture[5];
	glEnable(GL_LIGHTING);

	return true;

}
void drawprojector()
{
	glPushMatrix();
	glTranslatef(-7.5, 20, -65);
	glRotatef(-45, 0, 1, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量
	glVertex3f(-40.0f, 50.0f, -50.0 + 40 * sqrt(2.0));
	glVertex3f(-40.0 + 40 * sqrt(2.0), 50.0f, -50.0f);
	glVertex3f(-40.0 + 40 * sqrt(2.0), pro_up_down, -50.0f);
	glVertex3f(-40.0f, pro_up_down, -50.0 + 40 * sqrt(2.0));
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(4.0f);
	glBegin(GL_LINES);
	glVertex3f(-25.0f, 80.0f, -15.0f);
	glVertex3f(-25.0f, 65.0f, -15.0f);
	glEnd();
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
	glTranslatef(-25.0f, 64.0f, -15.0f);
	glScalef(4.0f, 2.0f, 2.0f);
	glutSolidCube(2.5f);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glutWireCube(2.5);
	glPopMatrix();
	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-7.5, 20, -65);
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-40.0f, 50.0f, -50.0 + 40 * sqrt(2.0));
	glVertex3f(-40.0 + 40 * sqrt(2.0), 50.0f, -50.0f);
	glVertex3f(-40.0 + 40 * sqrt(2.0), pro_up_down, -50.0f);
	glVertex3f(-40.0f, pro_up_down, -50.0 + 40 * sqrt(2.0));
	glEnd();
	glLineWidth(1.0f);
	glPopMatrix();
}
void projectup()
{
	pro_up_down = pro_up_down + 1.0f;
	if (pro_up_down >= 47.0f)
		pro_up_down = 47.0f;
	glutPostRedisplay();

}
void projectdown()
{
	pro_up_down = pro_up_down - 1.0f;
	if (pro_up_down <= -10.0f)
		pro_up_down = -10.0f;
	glutPostRedisplay();

}

/*用于定义键盘操作*/
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		sz += 5.50f;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_DOWN)
	{
		sz -= 5.50f;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_LEFT)
	{
		sx += 0.50f;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_RIGHT)
	{
		sx -= 0.50f;
		glutPostRedisplay();
	}
}


void keyboard(unsigned char key, int x, int y)

{

	switch (key)

	{

	case 'w':

	{

		updown -= 5.0;

		glutPostRedisplay();


	}

	break;

	case 's':

	{

		updown += 5.0;

		glutPostRedisplay();

	}

	break;

	case 'a':

	{

		angle += 5.0;

		glutPostRedisplay();

	}

	break;

	case 'd':

	{

		angle -= 5.0;

		glutPostRedisplay();

	}

	break;
	case 'r':

	{

		angle = 0.0;
		rud = 0.0;

		glutPostRedisplay();

	}
	case 'e':

	{

		sx = 0;
		sy = 0;
		sz = 0;
		updown = 0;
		glutPostRedisplay();

	}

	break;
	case 'i':

	{

		rud += 5;
		glutPostRedisplay();

	}

	break;
	case 'k':

	{

		rud -= 5;
		glutPostRedisplay();

	}

	break;
	case 'y':
	{
		projectup();
		glutPostRedisplay();
	}
	break;
	case 'h':
	{
		projectdown();
		glutPostRedisplay();
	}
	break;
	case 'g':
	{
		textemp[0] = texture[17];
		textemp[1] = texture[15];
		textemp[2] = texture[16];
		if (j <= 1)
			j += 1;
		else
			j = 0;
		texTV = textemp[j];
		glutPostRedisplay();
	}
	break;
	case 'f':
	{

		if (k <= 0)
		{
			k += 1;
			textempsky[0] = texture[18];
			textempsky[1] = texture[19];
			textempsky[2] = texture[20];
			textempsky[3] = texture[21];
			textempsky[4] = texture[22];
			textempsky[5] = texture[23];
		}
		else
		{
			k = 0;
			textempsky[0] = texture[0];
			textempsky[1] = texture[1];
			textempsky[2] = texture[2];
			textempsky[3] = texture[3];
			textempsky[4] = texture[4];
			textempsky[5] = texture[5];
		}
		glutPostRedisplay();
	}
	break;
	case 'o':
	{
		doorFlag ^= true;
		glutPostRedisplay();
	}
	break;
	}

}

void SkyBox()
{


	glPushMatrix();
	glScalef(100.0, 100.0, 100.0);
	glTranslatef(0, 1.0, 0);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textempsky[1]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textempsky[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textempsky[4]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textempsky[5]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textempsky[2]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textempsky[3]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, -10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void shadi()
{
	glPushMatrix();
	glScalef(30.0, 10.0, 30.0);
	glRotatef(45, 0, 1.0, 0);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 10.0f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(10.0f, -2.0f, 10.0f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(10.0f, -2.0f, -10.0f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(-10.0f, -2.0f, -10.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void diban()
{
	glPushMatrix();
	glScalef(10.0, 9.7, 10.0);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[10]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 10.0f);
	glTexCoord2f(3.0f, 0.0f); glVertex3f(10.0f, -2.0f, 10.0f);
	glTexCoord2f(3.0f, 4.0f); glVertex3f(10.0f, -2.0f, -10.0f);
	glTexCoord2f(0.0f, 4.0f); glVertex3f(-10.0f, -2.0f, -10.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void qiang()
{
	glPushMatrix();
	glScalef(10.0, 10.0, 10.0);
	glEnable(GL_TEXTURE_2D);



	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//尖顶的三角形
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 8.5f, -10.4f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-10.0f, 8.5f, 10.4f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 15.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 15.5f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//尖顶的后三角形
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 8.5f, -10.4f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(10.0f, 8.5f, 10.4f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 15.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 15.5f, 0.0f);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[24]);
	glBegin(GL_QUADS);

	//前方墙
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-11.0f, 8.48f, -10.5f);
	glTexCoord2f(4.0f, 0.0f); glVertex3f(11.0f, 8.48f, -10.5f);
	glTexCoord2f(4.0f, 3.0f); glVertex3f(11.0f, 15.82f, 0.0f);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-11.0f, 15.82f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[24]);
	glBegin(GL_QUADS);

	//Front
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-11.0f, 8.48f, 10.5f);
	glTexCoord2f(4.0f, 0.0f); glVertex3f(11.0f, 8.48f, 10.5f);
	glTexCoord2f(4.0f, 3.0f); glVertex3f(11.0f, 15.82f, 0.0f);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-11.0f, 15.82f, 0.0f);
	glEnd();





	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);

	//Front
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -2.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 8.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//Back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -2.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 8.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, 10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -2.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -2.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 8.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 8.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//left1
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 8.0f, -3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//left2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 8.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, 10.0f);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void bizhi()
{
	glPushMatrix();
	glScalef(9.9, 10, 9.9);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	//left22
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 6.0f, -3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, 6.0f, 3.0f);
	glTexCoord2f(1.0f, 0.2f); glVertex3f(-10.0f, 8.0f, 3.0f);
	glTexCoord2f(0.0f, 0.2f); glVertex3f(-10.0f, 8.0f, -3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);

	//Front
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -10.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(10.0f, -2.0f, -10.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(10.0f, 8.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	//Back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 10.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(10.0f, -2.0f, 10.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(10.0f, 8.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, 10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -2.0f, -10.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(10.0f, -2.0f, 10.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(10.0f, 8.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 8.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	//left1
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 8.0f, -3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	//left2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 8.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, 10.0f);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void men()
{
	glPushMatrix();
	glScalef(10.0, 10.0, 10.0);
	glEnable(GL_TEXTURE_2D);



	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_QUADS);
	//left1
	if (doorFlag) {
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 6.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 6.0f, -3.0f);
	}
	else {
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, -3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-12.12f, -2.0f, -0.87f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-12.12f, 6.0f, -0.87f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 6.0f, -3.0f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_QUADS);
	//left2
	if (doorFlag) {
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 6.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 6.0f, 3.0f);
	}
	else {
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -2.0f, 3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-12.12f, -2.0f, 0.87f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-12.12f, 6.0f, 0.87f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 6.0f, 3.0f);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//left2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 6.0f, -3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, 6.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 8.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 8.0f, -3.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void chuanghu()
{
	glPushMatrix();
	glScalef(10.0, 10.0, 10.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[25]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.02f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.02f, 1.0f, 4.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.02f, 6.0f, 4.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.02f, 6.0f, 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[25]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(9.88f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(9.88f, 1.0f, 4.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(9.88f, 6.0f, 4.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(9.88f, 6.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

void kongtiao()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[11]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(85.0f, -20.0f, -85.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, -20.0f, -85.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 45.0f, -85.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(85.0f, 45.0f, -85.0f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -20.0f, -98.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -20.0f, -98.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 80.0f, -98.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 80.0f, -98.0f);

	glEnd();
	//tv
	glBindTexture(GL_TEXTURE_2D, texture[13]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-30.0f, 0.0f, -97.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(30.0f, 0.0f, -97.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(30.0f, 40.0f, -97.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-30.0f, 40.0f, -97.0f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, texTV);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-29.0f, 1.0f, -96.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(29.0f, 1.0f, -96.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(29.0f, 39.0f, -96.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-29.0f, 39.0f, -96.5f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[12]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(85.0f, -20.0f, -85.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(85.0f, 45.0f, -85.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(85.0f, 45.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(85.0f, -20.0f, -100.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void zhuomian()
{
	glPushMatrix();
	glScalef(25.0, 1, 25.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[14]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.6f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.6f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 0.6f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.6f, -1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[14]);
	glBegin(GL_QUADS);
	//Front
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.5f, -1.001f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -0.5f, -1.001f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 0.5f, -1.001f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.5f, -1.001f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[14]);
	glBegin(GL_QUADS);
	//Back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.5f, 1.001f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -0.5f, 1.001f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 0.5f, 1.001f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.5f, 1.001f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.001f, -0.5f, -1.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(1.001f, -0.5f, 1.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(1.001f, 0.5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.001f, 0.5f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.001f, -0.5f, -1.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(-1.001f, -0.5f, 1.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(-1.001f, 0.5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.001f, 0.5f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void fangding()
{


	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glTranslatef(0, 120, 50);
	glRotatef(35, 1, 0, 0);
	glScalef(220, 5, 125);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glTranslatef(0, 120, -50);
	glRotatef(-35, 1, 0, 0);
	glScalef(220, 5, 125);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
void draw()
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (lflag)
		glEnable(GL_LIGHT0);
	if (rflag)
		glEnable(GL_LIGHT1);
	glPushMatrix();
	glTranslatef(sx, updown, sz);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glRotatef(rud, 1.0, 0.0, 0.0);
	diban();
	kongtiao();
	SkyBox();
	chuanghu();
	shadi();
	qiang();
	men();
	bizhi();
	drawprojector();
	zhuomian();
	fangding();
	//绘制地面；
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glTranslatef(0, -20, 0);
	glScalef(200, 1, 200);
	glCallList(drawcube);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glutWireCube(1);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	//绘制floor；
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(0, 80, 0);
	glScalef(220, 10, 220);
	glCallList(drawcube);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glutWireCube(1);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(0, 79, 0);
	glScalef(199, 1, 199);
	glCallList(drawcube);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glutWireCube(1);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	//menzhu
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(-106.2, 40, 106.2);
	glScalef(15, 120, 15);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(-106.2, 40, -106.2);
	glScalef(15, 120, 15);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(106.2, 40, 106.2);
	glScalef(15, 120, 15);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(106.2, 40, -106.2);
	glScalef(15, 120, 15);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();


	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(-100, 30, 37.5);
	glScalef(15, 100, 15);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(-100, 30, -37.5);
	glScalef(15, 100, 15);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();



	//backgroud 
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(-50, 30, -97);
	glScalef(15, 100, 5);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(50, 30, -97);
	glScalef(15, 100, 5);
	glCallList(drawcube);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glTranslatef(0, 72.5, -97);
	glScalef(100, 15, 5);
	glCallList(drawcube);
	//glColor4f(0.5,0.5,0.5,1.0);
 //glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	//绘制四个桌腿：
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.2, 0.22, 0.2, 1.0);
	glTranslatef(20, -10, -20);
	glScalef(1, 20, 1);
	glCallList(drawcube);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.2, 0.22, 0.2, 1.0);
	glTranslatef(-20, -10, -20);
	glScalef(1, 20, 1);
	glCallList(drawcube);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.2, 0.22, 0.2, 1.0);
	glTranslatef(-20, -10, 20);
	glScalef(1, 20, 1);
	glCallList(drawcube);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.2, 0.22, 0.2, 1.0);
	glTranslatef(20, -10, 20);
	glScalef(1, 20, 1);
	glCallList(drawcube);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//画出桌面：
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.1, 1.0, 0.1, 0.0);
	glScalef(50, 1, 50);
	glCallList(drawcube);
	glColor4f(0.39, 0.30, 0.1, 0.0);
	glutWireCube(1);
	// glFlush();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	//绘制两边台阶；
	glPushMatrix();//左边第一级台阶
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.51, 0.40, 0.1, 0.0);
	glTranslatef(-30, -12, 0);
	glScalef(10, 4, 50);
	glCallList(drawcube);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.1, 0.50, 0.51, 0.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();// 右边第一级台阶
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.51, 0.40, 0.1, 0.0);
	glTranslatef(40, -12, 0);
	glScalef(10, 4, 50);
	glCallList(drawcube);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.1, 0.50, 0.51, 0.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();//左边第二级台阶
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.51, 0.40, 0.1, 0.0);
	glTranslatef(-32.5, -8, 0);
	glScalef(5, 4, 50);
	glCallList(drawcube);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.1, 0.50, 0.51, 0.0);
	glutWireCube(1);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPushMatrix();//右边第二级台阶
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.51, 0.40, 0.1, 0.0);
	glTranslatef(42.5, -8, 0);
	glScalef(5, 4, 50);
	glCallList(drawcube);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.1, 0.50, 0.51, 0.0);
	glutWireCube(1);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glPushMatrix(); //地面上放置 圆锥体；
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.01, 0.01, 0.81, 0.0);
	glPopMatrix();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();

}

void  main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	InitGL();

	glutReshapeFunc(reshape);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(draw);

	glutMainLoop();

}