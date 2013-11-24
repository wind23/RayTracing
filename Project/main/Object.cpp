#include "Object.h"
#include "stdafx.h"

Object::Object(int t,void *p)
	:type(t),ptr(p),LocalColor(NULL),LocalNormal(NULL)
{
}

Vector Object::Normal(Vector node)
{
	Vector add(0,0,0);
	if(LocalNormal!=NULL)
	{
		add=LocalNormal(node);
	}
	switch(type)
	{
	case _PLANE:
		return add+((Plane*)ptr)->Normal(node);
	case _BALL:
		return add+((Ball*)ptr)->Normal(node);
	case _TRIANGLE:
		return add+((Triangle*)ptr)->Normal(node);
	case _PARALLELOGRAM:
		return add+((Parallelogram*)ptr)->Normal(node);
	case _CIRCLE:
		return add+((Circle*)ptr)->Normal(node);
	case _RING:
		return add+((Ring*)ptr)->Normal(node);
	case _CYLINDER:
		return add+((Cylinder*)ptr)->Normal(node);
	}
	return *(Vector*)NULL;
}

Source::Source(Vector _pos, Color _light)
	:pos(_pos), light(_light)
{
}

Ray::Ray(Vector _end, Vector _direction)
	:end(_end), direction(_direction)
{
}

double Ray::Intersection(Object obj)
{
	switch(obj.type)
	{
	case _PLANE:
		{
			Plane& p=*(Plane*)(obj.ptr);
			return (p.normal&(p.pos-end))/(p.normal&direction);
		}
	case _BALL:
		{
			Ball& p=*(Ball*)(obj.ptr);
			double t1=direction&direction;
			Vector v=p.pos-end;
			double t2=direction&v;
			double t3=v&v;
			double r1=(t2-sqrt(t2*t2-t1*(t3-p.r*p.r)))/t1;
			if(r1>0.000001)
			{
				return r1;
			}
			if(r1<=0.000001)
			{
				double r2=(t2+sqrt(t2*t2-t1*(t3-p.r*p.r)))/t1;
				if(r2>0.000001)
				{
					return r2;
				}
			}
			return -1;
		}
	case _TRIANGLE:
		{
			Triangle& p=*(Triangle*)(obj.ptr);
			Vector v1=end-p.n1,v2=p.n2-p.n1,v3=p.n3-p.n1;
			double k23=-(direction.x*v2.y*v1.z-direction.x*v2.z*v1.y+v2.x*v1.y*direction.z-v2.x*v1.z*direction.y+v1.x*direction.y*v2.z-v1.x*direction.z*v2.y);
			double k22=-(direction.x*v1.y*v3.z-direction.x*v1.z*v3.y+v1.x*v3.y*direction.z-v1.x*v3.z*direction.y+v3.x*direction.y*v1.z-v3.x*direction.z*v1.y);
			double k21=v1.x*v2.y*v3.z-v1.x*v2.z*v3.y+v2.x*v3.y*v1.z-v2.x*v3.z*v1.y+v3.x*v1.y*v2.z-v3.x*v1.z*v2.y;
			double k1=-(direction.x*v2.y*v3.z-direction.x*v2.z*v3.y+v2.x*v3.y*direction.z-v2.x*v3.z*direction.y+v3.x*direction.y*v2.z-v3.x*direction.z*v2.y);
			double k=k21/k1;
			double mu=k23/k1;
			double lambda=k22/k1;
			if(k>=0.000001&&mu>=0.000001&&lambda>=0.000001&&mu+lambda<=0.999999)
			{
				return k;
			}
			else
			{
				return -1;
			}
		}
	case _PARALLELOGRAM:
		{
			Parallelogram& p=*(Parallelogram*)(obj.ptr);
			Vector v1=end-p.pos,v2=p.v1,v3=p.v2;
			double k23=-(direction.x*v2.y*v1.z-direction.x*v2.z*v1.y+v2.x*v1.y*direction.z-v2.x*v1.z*direction.y+v1.x*direction.y*v2.z-v1.x*direction.z*v2.y);
			double k22=-(direction.x*v1.y*v3.z-direction.x*v1.z*v3.y+v1.x*v3.y*direction.z-v1.x*v3.z*direction.y+v3.x*direction.y*v1.z-v3.x*direction.z*v1.y);
			double k21=v1.x*v2.y*v3.z-v1.x*v2.z*v3.y+v2.x*v3.y*v1.z-v2.x*v3.z*v1.y+v3.x*v1.y*v2.z-v3.x*v1.z*v2.y;
			double k1=-(direction.x*v2.y*v3.z-direction.x*v2.z*v3.y+v2.x*v3.y*direction.z-v2.x*v3.z*direction.y+v3.x*direction.y*v2.z-v3.x*direction.z*v2.y);
			double k=k21/k1;
			double mu=k23/k1;
			double lambda=k22/k1;
			if(k>=0.000001&&mu>=0.000001&&lambda>=0.000001&&mu<=0.999999&&lambda<=0.999999)
			{
				return k;
			}
			else
			{
				return -1;
			}
		}
	case _CIRCLE:
		{
			Circle& p=*(Circle*)(obj.ptr);
			double k=(p.normal&(p.pos-end))/(p.normal&direction);
			Vector kr=end+k*direction;
			double dis=~(kr-p.pos);
			if(dis<p.r-0.000001&&k>0.000001)
			{
				return k;
			}
			else
			{
				return -1;
			}
		}
	case _RING:
		{
			Ring& p=*(Ring*)(obj.ptr);
			double k=(p.normal&(p.pos-end))/(p.normal&direction);
			Vector kr=end+k*direction;
			double dis=~(kr-p.pos);
			if(dis<p.r1-0.000001&&dis>p.r2+0.000001&&k>0.000001)
			{
				return k;
			}
			else
			{
				return -1;
			}
		}
	case _CYLINDER:
		{
			Cylinder& p=*(Cylinder*)(obj.ptr);
			Vector u=!(p.dir);
			Vector v=end-p.pos;
			double a1=u.x*(v&u)-v.x;
			double a2=u.y*(v&u)-v.y;
			double a3=u.z*(v&u)-v.z;
			double b1=u.x*(direction&u)-direction.x;
			double b2=u.y*(direction&u)-direction.y;
			double b3=u.z*(direction&u)-direction.z;
			double a=b1*b1+b2*b2+b3*b3;
			double b=2*(a1*b1+a2*b2+a3*b3);
			double c=a1*a1+a2*a2+a3*a3-p.r*p.r;
			if(b*b-4*a*c<0)
			{
				return -1;
			}
			double k1=(-b-sqrt(b*b-4*a*c))/(2*a);
			Vector nd=end+k1*direction-p.pos;
			double rt=nd&u;
			if(rt>=0.000001&&rt<=p.l-0.000001)
			{
				return k1;
			}
			double k2=(-b+sqrt(b*b-4*a*c))/(2*a);
			nd=end+k2*direction-p.pos;
			rt=nd&u;
			if(rt>=0.000001&&rt<=p.l-0.000001)
			{
				return k2;
			}
			return -1;
		}
	default:
		return -1;
	}
}

Inter Ray::Intersection(Scene& sc)
{
	double km=1.e99;
	int index=-1;
	int sz=sc.obj.size();
	for(int i=0;i<sz;i++)
	{
		double k=Intersection(sc.obj[i]);
		if(k>0.00001&&k<km)
		{
			km=k;
			index=i;
		}
	}
	if(index>=0)
	{
		return Inter(km,index);
	}
	else
	{
		return Inter(-1,-1);
	}
}

Ray Ray::Reflection(Object obj,Vector inter)
{
	Vector normal=!obj.Normal(inter);
	Vector dir1=-direction;
	Vector normaln=normal*(normal&dir1);
	Vector dir2=normaln*2-dir1;
	return Ray(inter,dir2);
}

Ray Ray::Refraction(Object obj,Vector inter)
{
	Vector normal=!obj.Normal(inter);
	double rfrt;
	if((direction&normal)<0)
	{
		rfrt=obj.prop.refractive_index;
	}
	else
	{
		rfrt=1./obj.prop.refractive_index;
		normal=-normal;
	}
	double th1=(-direction)^normal;
	if(th1<0.000001||th1>3.141592)
	{
		return Ray(inter,direction);
	}
	double s2=sin(th1)*rfrt;
	if(s2>0.999999)
	{
		return Ray(inter,Vector(0.,0.,0.));
	}
	double th2=asin(s2);
	Vector v1=-direction*(1/(normal&direction));
	Vector v2=normal+v1;
	Vector v3=(!v2)*tan(th2);
	return Ray(inter,v3-normal);
}

Plane::Plane(Vector _pos, Vector _normal)
	:pos(_pos), normal(_normal)
{
}

Vector Plane::Normal(Vector node)
{
	return normal;
}

Parallelogram::Parallelogram(Vector _pos, Vector _v1, Vector _v2)
	:pos(_pos), v1(_v1), v2(_v2)
{
}

Vector Parallelogram::Normal(Vector node)
{
	return -v1*v2;
}

Triangle::Triangle(Vector _n1, Vector _n2, Vector _n3)
	:n1(_n1), n2(_n2), n3(_n3)
{
}

Vector Triangle::Normal(Vector node)
{
	return -(n2-n1)*(n3-n1);
}

Circle::Circle(Vector _pos, Vector _normal, double _r)
	:pos(_pos), normal(_normal), r(_r)
{
}

Vector Circle::Normal(Vector node)
{
	return normal;
}

Ring::Ring(Vector _pos, Vector _normal, double _r1, double _r2)
	:pos(_pos), normal(_normal), r1(_r1), r2(_r2)
{
}

Vector Ring::Normal(Vector node)
{
	return normal;
}

Ball::Ball(Vector _pos, double _r)
	:pos(_pos), r(_r)
{
}

Vector Ball::Normal(Vector node)
{
	return node-pos;
}

Cylinder::Cylinder(Vector _pos, Vector _dir, double _r, double _l)
	:pos(_pos), dir(_dir), r(_r), l(_l)
{
}

Vector Cylinder::Normal(Vector node)
{
	Vector udir=!dir;
	Vector arr=node-pos;
	return arr-(udir&arr)*udir;
}