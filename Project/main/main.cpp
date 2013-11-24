#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include<cmath>
#include <Windows.h>

int ConvertColor(Color c);
Ratio Ceiling(Vector node);
Vector Ground(Vector node);

int _tmain(int argc, _TCHAR* argv[])
{
	char vo;
	cout << "是否生成漫游视频：(Y/N)" ;
	cin >> vo ;
	if(vo=='y'||vo=='Y')
	{
		vo=1;
	}
	else
	{
		vo=0;
	}
	Scene sc;
	srand(unsigned(time(NULL)));
	vector<Ball> ball;
	vector<Plane> plane;
	vector<Triangle> triangle;
	vector<Parallelogram> parallelogram;
	vector<Circle> circle;
	vector<Ring> ring;
	vector<Cylinder> cylinder;

	ball.push_back(Ball(Vector(350,170,750),200));
	ball.push_back(Ball(Vector(250,420,1100),100));
	plane.push_back(Plane(Vector(0,0,2000),Vector(0,1,-1)));
	plane.push_back(Plane(Vector(0,500,2000),Vector(0,-1,-1)));
	plane.push_back(Plane(Vector(-500,0,0),Vector(-1,0,0)));
	plane.push_back(Plane(Vector(1000,0,0),Vector(1,0,0)));
	plane.push_back(Plane(Vector(0,0,-1000),Vector(0,1,1)));
	plane.push_back(Plane(Vector(0,500,-1000),Vector(0,-1,1)));
	//Vector loc=Vector(-300,300,300);
	Vector loc=Vector(200,580,0);
	triangle.push_back(Triangle(Vector(100,170,750)+loc,Vector(350,-80,750)+loc,Vector(350,170,500)+loc));
	triangle.push_back(Triangle(Vector(350,170,500)+loc,Vector(350,-80,750)+loc,Vector(600,170,750)+loc));
	triangle.push_back(Triangle(Vector(600,170,750)+loc,Vector(350,-80,750)+loc,Vector(350,170,1000)+loc));
	triangle.push_back(Triangle(Vector(350,170,1000)+loc,Vector(350,-80,750)+loc,Vector(100,170,750)+loc));
	triangle.push_back(Triangle(Vector(350,170,500)+loc,Vector(350,420,750)+loc,Vector(100,170,750)+loc));
	triangle.push_back(Triangle(Vector(100,170,750)+loc,Vector(350,420,750)+loc,Vector(350,170,1000)+loc));
	triangle.push_back(Triangle(Vector(350,170,1000)+loc,Vector(350,420,750)+loc,Vector(600,170,750)+loc));
	triangle.push_back(Triangle(Vector(600,170,750)+loc,Vector(350,420,750)+loc,Vector(350,170,500)+loc));
	ball.push_back(Ball(Vector(350,170,750)+loc,100));
	cylinder.push_back(Cylinder(Vector(1000,-200,1000),Vector(-1,0,0),150,400));
	circle.push_back(Circle(Vector(600,-200,1000),Vector(-1,0,0),150));
	
	sc.obj.push_back(Object(_BALL,&ball[0]));
	sc.obj[0].prop.refraction=Ratio(0.9,0.9,0.9);
	sc.obj[0].prop.specular_reflection=Ratio(0.05,0.05,0.05);
	sc.obj[0].prop.diffuse_reflection=Ratio(0.02,0.02,0.02);
	sc.obj[0].prop.refractive_index=2./3.;
	sc.obj.push_back(Object(_BALL,&ball[1]));
	sc.obj[1].prop.refraction=Ratio(0,0,0);
	sc.obj[1].prop.specular_reflection=Ratio(0.5,0.5,0.5);
	sc.obj[1].prop.diffuse_reflection=Ratio(0.25,0.5,0.25);
	sc.obj[1].prop.refractive_index=0;
	sc.obj.push_back(Object(_PLANE,&plane[0]));
	sc.obj[2].prop.refraction=Ratio(0,0,0);
	sc.obj[2].prop.specular_reflection=Ratio(0.8,0.8,0.8);
	sc.obj[2].prop.diffuse_reflection=Ratio(0.1,0.1,0.1);
	sc.obj[2].prop.refractive_index=0;
	sc.obj.push_back(Object(_PLANE,&plane[1]));
	sc.obj[3].prop.refraction=Ratio(0,0,0);
	sc.obj[3].prop.specular_reflection=Ratio(0.8,0.8,0.8);
	sc.obj[3].prop.diffuse_reflection=Ratio(0.1,0.1,0.1);
	sc.obj[3].prop.refractive_index=0;
	sc.obj.push_back(Object(_PLANE,&plane[2]));
	sc.obj[4].prop.refraction=Ratio(0,0,0);
	sc.obj[4].prop.specular_reflection=Ratio(0.4,0.4,0.4);
	sc.obj[4].prop.diffuse_reflection=Ratio(0.1,0.5,0.2);
	sc.obj[4].prop.refractive_index=0;
	sc.obj[4].LocalColor=Ceiling;
	sc.obj.push_back(Object(_PLANE,&plane[3]));
	sc.obj[5].prop.refraction=Ratio(0,0,0);
	sc.obj[5].prop.specular_reflection=Ratio(0.1,0.1,0.1);
	sc.obj[5].prop.diffuse_reflection=Ratio(0.1,0.2,0.7);
	sc.obj[5].prop.refractive_index=0;
	sc.obj[5].LocalNormal=Ground;
	sc.obj.push_back(Object(_PLANE,&plane[4]));
	sc.obj[6].prop.refraction=Ratio(0,0,0);
	sc.obj[6].prop.specular_reflection=Ratio(0.1,0.1,0.1);
	sc.obj[6].prop.diffuse_reflection=Ratio(0.5,0.5,0.5);
	sc.obj[6].prop.refractive_index=0;
	sc.obj.push_back(Object(_PLANE,&plane[5]));
	sc.obj[7].prop.refraction=Ratio(0,0,0);
	sc.obj[7].prop.specular_reflection=Ratio(0.1,0.1,0.1);
	sc.obj[7].prop.diffuse_reflection=Ratio(0.5,0.5,0.7);
	sc.obj[7].prop.refractive_index=0;
	for(int k=0;k<8;k++)
	{
		sc.obj.push_back(Object(_TRIANGLE,&triangle[k]));
		sc.obj[8+k].prop.refraction=Ratio(0.7,0.7,0.7);
		sc.obj[8+k].prop.specular_reflection=Ratio(0.2,0.2,0.2);
		sc.obj[8+k].prop.diffuse_reflection=Ratio(0.05,0.05,0.05);
		sc.obj[8+k].prop.refractive_index=2./3.;
	}
	sc.obj.push_back(Object(_BALL,&ball[2]));
	sc.obj[16].prop.refraction=Ratio(0.,0.,0.);
	sc.obj[16].prop.specular_reflection=Ratio(0.05,0.05,0.05);
	sc.obj[16].prop.diffuse_reflection=Ratio(0.9,0.,0.);
	sc.obj[16].prop.refractive_index=0;
	sc.obj.push_back(Object(_CYLINDER,&cylinder[0]));
	sc.obj[17].prop.refraction=Ratio(0.,0.,0.);
	sc.obj[17].prop.specular_reflection=Ratio(0.5,0.5,0.5);
	sc.obj[17].prop.diffuse_reflection=Ratio(0.4,0.,0.);
	sc.obj[17].prop.refractive_index=0;
	sc.obj.push_back(Object(_CIRCLE,&circle[0]));
	sc.obj[18].prop.refraction=Ratio(0.,0.,0.);
	sc.obj[18].prop.specular_reflection=Ratio(0.5,0.5,0.5);
	sc.obj[18].prop.diffuse_reflection=Ratio(0.3,0.2,0.);
	sc.obj[18].prop.refractive_index=0;

	sc.src.push_back(Source(Vector(-500,-500,-500),Color(2000000000,2000000000,2000000000)));
	if(vo==0)
	{
		IplImage *image=cvCreateImage(cvSize(1000,1000),IPL_DEPTH_8U,3);
		for(int i=0;i<1000;i++)
		{
			cout << i << endl ;
			for(int j=0;j<1000;j++)
			{
				if(i==500&&j==500)
				{
					int ji=1;
				}
				Ray ray(Vector(250,250,-1000),Vector(i-500,j-500,1000));
				Color c=ray.IntersectColor(sc,Ratio(1.,1.,1.));
				int b=ConvertColor(c);
				image->imageData[(image->width*i+j)*3]=b&0xff;
				image->imageData[(image->width*i+j)*3+1]=(b&0xff00)>>8;
				image->imageData[(image->width*i+j)*3+2]=(b&0xff0000)>>16;
			}
		}
		cvSaveImage("output.bmp",image);
		cvReleaseImage(&image);
	}
	else
	{
		double fps=24;
		CvSize size=cvSize(1280,720);
		CvVideoWriter *writer=cvCreateVideoWriter("output.avi",CV_FOURCC('M','J','P','G'),fps,size);
		IplImage *image=cvCreateImage(size,IPL_DEPTH_8U,3);
		int time=GetTickCount();
		for(int i=0;i<720;i++)
		{
			cout << i << '\t' << GetTickCount()-time << endl ;
			for(int j=0;j<720;j++)
			{
				for(int k=0;k<1280;k++)
				{
					double th=i/360.*PI;
					double r=(k-640.)*1000./768.;
					double lg=750*sqrt(2.)/cos(PI/4-(i%180)/360.*PI);
					Vector mov=Vector(0,lg*sin(th),-lg*cos(th));
					Ray ray(Vector(250,250,500)+mov,
						Vector(j/768.*1000.-500,sin(atan(r/1000.)-th)*sqrt(1000000+r*r),cos(atan(r/1000.)-th)*sqrt(1000000+r*r)));
					Color c=ray.IntersectColor(sc,Ratio(1.,1.,1.));
					int b=ConvertColor(c);
					image->imageData[(image->width*j+k)*3]=b&0xff;
					image->imageData[(image->width*j+k)*3+1]=(b&0xff00)>>8;
					image->imageData[(image->width*j+k)*3+2]=(b&0xff0000)>>16;
				}
			}
			char filename[20];
			sprintf(filename,"output%04d.bmp",i);
			cvSaveImage(filename,image);
			cvWriteFrame(writer,image);
		}
		cvReleaseVideoWriter(&writer);
		cvReleaseImage(&image);
	}
	return 0;
}

int ConvertColor(Color c)
{
	int cr,cg,cb;
	cr=c.r>255?255:c.r;
	cg=c.g>255?255:c.g;
	cb=c.b>255?255:c.b;
	return (cr<<16)|(cg<<8)|(cb);
#if 0
	if(c.b<255.5&&c.g<255.5&&c.r<255.5)
	{
		return ((int)(c.r)<<16)|((int)(c.g)<<8)|((int)(c.b));
	}
	double r,g,b;
	if(c.r>=255.5)
	{
		r=255;
		g=255-((255-c.g)*(255-c.r+255-c.g+255-c.b))/(255-c.g+255-c.b);
		b=255-((255-c.b)*(255-c.r+255-c.g+255-c.b))/(255-c.g+255-c.b);
		if(g>=255.5)
		{
			double d=g-255;
			g-=d;
			b+=d;
			if(b>=255.5)
			{
				return 0xffffff;
			}
			return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
		}
		else if(b>=255.5)
		{
			double d=b-255;
			b-=d;
			g+=d;
			if(g>=255.5)
			{
				return 0xffffff;
			}
			return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
		}
		return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
	}
	else if(c.g>=255.5)
	{
		r=255-((255-c.r)*(255-c.r+255-c.g+255-c.b))/(255-c.r+255-c.b);
		g=255;
		b=255-((255-c.b)*(255-c.r+255-c.g+255-c.b))/(255-c.r+255-c.b);
		if(r>=255.5)
		{
			double d=r-255;
			r-=d;
			b+=d;
			if(b>=255.5)
			{
				return 0xffffff;
			}
			return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
		}
		else if(b>=255.5)
		{
			double d=b-255;
			b-=d;
			r+=d;
			if(r>=255.5)
			{
				return 0xffffff;
			}
			return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
		}
		return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
	}
	else if(c.b>=255.5)
	{
		r=255-((255-c.r)*(255-c.r+255-c.g+255-c.b))/(255-c.r+255-c.g);
		g=255-((255-c.g)*(255-c.r+255-c.g+255-c.b))/(255-c.r+255-c.g);
		b=255;
		if(g>=255.5)
		{
			double d=g-255;
			g-=d;
			r+=d;
			if(r>=255.5)
			{
				return 0xffffff;
			}
			return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
		}
		else if(r>=255.5)
		{
			double d=r-255;
			r-=d;
			g+=d;
			if(g>=255.5)
			{
				return 0xffffff;
			}
			return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
		}
		return ((int)(r)<<16)|((int)(g)<<8)|((int)(b));
	}
	return ((int)(c.r)<<16)|((int)(c.g)<<8)|((int)(c.b));
#endif
}

Ratio Ceiling(Vector node)
{
	double p1=node.y+node.z;
	double p2=node.y-node.z;
	if(((int)floor(p1/600)+(int)floor(p2/600))%2)
	{
		return Ratio(0.1,0.5,0.2);
	}
	else
	{
		return Ratio(0.05,0.05,0.05);
	}
}

Vector Ground(Vector node)
{
	double p1=(node.y+node.z)/20.;
	double p2=(node.y-node.z)/20.;
	double s1=sin(p1);
	double s2=sin(p2);
	return Vector(0,s1+s2,s1-s2);
	//double c1=p1/30
}