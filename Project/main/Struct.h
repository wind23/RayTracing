#ifndef _STRUCT
#define _STRUCT

class Ratio;

class Vector
{
public:
	double x;
	double y;
	double z;
	Vector(double px,double py,double pz);
	friend const Vector operator+(const Vector& a1, const Vector& a2);
	friend const Vector operator+(const Vector& a);
	friend const Vector operator-(const Vector& a1, const Vector& a2);
	friend const Vector operator-(const Vector& a);
	friend const Vector operator*(const Vector& a1, const Vector& a2);
	friend const Vector operator*(double k, const Vector& a2);
	friend const Vector operator*(const Vector& a2,double k);
	friend const double operator&(const Vector& a1, const Vector& a2);
	friend const double operator~(const Vector& a);
	friend const Vector operator!(const Vector& a);
	friend const double operator^(const Vector& a1, const Vector& a2);
	friend std::ostream& operator<<(std::ostream& os, const Vector& a);
};

class Color
{
public:
	double r;
	double g;
	double b;
	Color();
	Color(double cr,double cg,double cb);
	friend std::ostream& operator<<(std::ostream& os, const Color& a);
	friend const Color operator*(const Color& color, const Ratio& ratio);
	friend const Color operator*(const Color& color, const double& ratio);
	friend const Color operator+(const Color& c1, const Color& c2);
};

class Ratio
{
public:
	double r;
	double g;
	double b;
	Ratio();
	Ratio(double cr,double cg,double cb);
	friend const Ratio operator*(const Ratio& r1, const Ratio& r2);
};

class Property
{
public:
	Ratio diffuse_reflection;
	Ratio specular_reflection;
	Ratio refraction;
	double refractive_index;
};

#endif