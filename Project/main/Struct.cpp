
#include "stdafx.h"

Vector::Vector(double px,double py,double pz)
	:x(px),y(py),z(pz)
{
}

const Vector operator+(const Vector& a1, const Vector& a2)
{
	return Vector(a1.x+a2.x,a1.y+a2.y,a1.z+a2.z);
}

const Vector operator+(const Vector& a)
{
	return a;
}

const Vector operator-(const Vector& a1, const Vector& a2)
{
	return Vector(a1.x-a2.x,a1.y-a2.y,a1.z-a2.z);
}

const Vector operator-(const Vector& a)
{
	return Vector(-a.x,-a.y,-a.z);
}

const Vector operator*(const Vector& a1, const Vector& a2)
{
	return Vector(a1.y*a2.z-a1.z*a2.y,a1.z*a2.x-a1.x*a2.z,a1.x*a2.y-a1.y*a2.x);
}

const Vector operator*(double k, const Vector& a2)
{
	return Vector(k*a2.x,k*a2.y,k*a2.z);
}

const Vector operator*(const Vector& a2,double k)
{
	return Vector(k*a2.x,k*a2.y,k*a2.z);
}

const double operator&(const Vector& a1, const Vector& a2)
{
	return a1.x*a2.x+a1.y*a2.y+a1.z*a2.z;
}

const double operator~(const Vector& a)
{
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

const double operator^(const Vector& a1, const Vector& a2)
{
	return acos((a1.x*a2.x+a1.y*a2.y+a1.z*a2.z)/sqrt((a1.x*a1.x+a1.y*a1.y+a1.z*a1.z)*(a2.x*a2.x+a2.y*a2.y+a2.z*a2.z)));
}

const Vector operator!(const Vector& a)
{
	return (1./~a)*a;
}

ostream& operator<<(std::ostream& os, const Vector& a)
{
	return os << '(' << a.x << ',' << a.y << ',' << a.z << ')' ;
}

Color::Color()
	:r(0),b(0),g(0)
{
}

Color::Color(double cr,double cg,double cb)
	:r(cr),b(cb),g(cg)
{
}

std::ostream& operator<<(std::ostream& os, const Color& a)
{
	return os << '(' << a.r << ',' << a.g << ',' << a.b << ')' ;
}

const Color operator*(const Color& color, const Ratio& ratio)
{
	return Color(color.r*ratio.r,color.g*ratio.g,color.b*ratio.b);
}

const Color operator*(const Color& color, const double& ratio)
{
	return Color(color.r*ratio,color.g*ratio,color.b*ratio);
}

const Color operator+(const Color& c1, const Color& c2)
{
	return Color(c1.r+c2.r,c1.g+c2.g,c1.b+c2.b);
}

Ratio::Ratio()
{
}

Ratio::Ratio(double cr,double cg,double cb)
	:r(cr),b(cb),g(cg)
{
}

const Ratio operator*(const Ratio& r1, const Ratio& r2)
{
	return Ratio(r1.r*r2.r,r1.g*r2.g,r1.b*r2.b);
}