#include "stdafx.h"

Color Ray::IntersectColor(Scene& sc, Ratio weight)
{
	Inter inter=Intersection(sc);
	if(inter.second>=0)
	{
		Color cl=LocalShading(sc,inter);
		//Color cl=Ambient(sc,inter);
		//cl=cl+LocalShading(sc,inter);
		Ratio reflect=sc.obj[inter.second].prop.specular_reflection;
		Ratio refract=sc.obj[inter.second].prop.refraction;
		if(weight.b>=1./256.||weight.g>=1./256||weight.r>=1./256)
		{
			Vector inter_node=end+inter.first*direction;
			if(reflect.b+reflect.g+reflect.r>=1./256)
			{
				Ray rfray=Reflection(sc.obj[inter.second],inter_node);
				cl=cl+rfray.IntersectColor(sc,weight*reflect)*reflect;
			}
			if(refract.b+refract.g+refract.r>=1./256)
			{
				Ray rfray=Refraction(sc.obj[inter.second],inter_node);
				cl=cl+rfray.IntersectColor(sc,weight*refract)*refract;
			}
		}
		//cout << cl << endl ;
		return cl;
	}
	else
	{
		//cout << "(0,0,0)" << endl ;
		return Color();
	}
}

/*Color Ray::Ambient(Scene& sc,Inter inter)
{
	int sz=sc.src.size();
	Color color;
	for(int i=0;i<sz;i++)
	{
		color=color+sc.src[i].light*(6.e-8)*sc.obj[inter.second].prop.diffuse_reflection;
	}
	return color;
}*/

Color Ray::LocalShading(Scene& sc,Inter inter)
{
	int sz=sc.src.size();
	Color color;
	Vector inter_node=end+direction*inter.first;
	Ratio localRatio=(sc.obj[inter.second].LocalColor==NULL?
		sc.obj[inter.second].prop.diffuse_reflection:sc.obj[inter.second].LocalColor(inter_node));
	for(int i=0;i<sz;i++)
	{
		double abr=6.e-8;
		color=color+sc.src[i].light*abr*localRatio;
	}
	Vector normal=sc.obj[inter.second].Normal(inter_node);
	for(int i=0;i<sz;i++)
	{
		Ray s=Ray(sc.src[i].pos,inter_node-sc.src[i].pos);
		double kr=s.Intersection(sc).first;
		if(!(kr>=0.00001&&kr<=0.99999))
		{
			double theta=(sc.src[i].pos-inter_node)^normal;
			if(cos(theta)>0)
			{
				color=color+sc.src[i].light*(1./(s.direction&s.direction))*localRatio*cos(theta);
			}
		
			Ray reflect=s.Reflection(sc.obj[inter.second],inter_node);
			double alpha=(-direction)^(reflect.direction);
			if(cos(alpha)>0)
			{
				Color add=sc.src[i].light*(1./(s.direction&s.direction))*sc.obj[inter.second].prop.specular_reflection*pow(cos(alpha),100);
				color=color+add;
			}
		}
	}
	return color;
}