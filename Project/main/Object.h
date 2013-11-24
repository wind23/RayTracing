#ifndef _OBJECT
#define _OBJECT

#define _PLANE 1
#define _PARALLELOGRAM 2
#define _TRIANGLE 3
#define _CIRCLE 4
#define _BALL 5
#define _CYLINDER 6
#define _RING 7
#include "Struct.h"

typedef std::pair<double,int> Inter;

class Object
{
public:
	int type;
	void *ptr;
	Property prop;
	Object(int t,void *p);
	Vector Normal(Vector node);
	Ratio (*LocalColor)(Vector node);
	Vector (*LocalNormal)(Vector node);
};

class Source
{
public:
	Vector pos;
	Color light;
	Source(Vector _pos, Color _light);
};

class Scene
{
public:
	vector<Object> obj;
	vector<Source> src;
};

class Ray
{
public:
	Vector end;
	Vector direction;
	Ray(Vector _end, Vector _direction);
	double Intersection(Object obj);
	Inter Intersection(Scene& sc);
	Color IntersectColor(Scene& sc, Ratio weight);
	//Color Ambient(Scene& sc,Inter inter);
	Color LocalShading(Scene& sc,Inter inter);
	Ray Reflection(Object obj,Vector inter);
	Ray Refraction(Object obj,Vector inter);
};

class Plane
{
public:
	Vector pos;
	Vector normal;
	Plane(Vector _pos, Vector _normal);
	Vector Normal(Vector node);
};

class Parallelogram
{
public:
	Vector pos;
	Vector v1,v2;
	Parallelogram(Vector _pos, Vector _v1, Vector _v2);
	Vector Normal(Vector node);
};

class Triangle
{
public:
	Vector n1,n2,n3;
	Triangle(Vector _n1, Vector _n2, Vector _n3);
	Vector Normal(Vector node);
};

class Circle
{
public:
	Vector pos;
	Vector normal;
	double r;
	Circle(Vector _pos, Vector _normal, double _r);
	Vector Normal(Vector node);
};

class Ring
{
public:
	Vector pos;
	Vector normal;
	double r1,r2;
	Ring(Vector _pos, Vector _normal, double _r1, double _r2);
	Vector Normal(Vector node);
};

class Ball
{
public:
	Vector pos;
	double r;
	Ball(Vector _pos, double r);
	Vector Normal(Vector node);
};

class Cylinder
{
public:
	Vector pos;
	Vector dir;
	double r;
	double l;
	Cylinder(Vector _pos, Vector _dir, double _r, double _l);
	Vector Normal(Vector node);
};

#endif