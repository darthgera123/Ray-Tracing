// class for defining spheres
#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
// #include "material.h"

class sphere:public hitable{
public:
	sphere() {}
	vec3 center;
	float radius;
	material *mat_ptr;
	sphere(vec3 cen,float r,material *m){
		center = cen;
		radius =r;
		mat_ptr = m;
	};
	virtual bool hit(const ray& r,float t_min,float t_max, hit_record& rec) const;
	
};
// function which will return the struct hit_record containing normal,value of t and if there is an intersection or not
bool sphere::hit(const ray&r,float t_min,float t_max,hit_record& rec)const{
	vec3 oc = r.origin()-center;
	float a = dot(r.direction(),r.direction());
	float b = dot(oc,r.direction());
	float c = dot(oc,oc)-radius*radius;
	float discrimiant = b*b-a*c;
	if (discrimiant>0){
		float temp = (-b-sqrt(discrimiant))/(a);
		if(temp<t_max && temp>t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p-center)/radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b+sqrt(discrimiant))/(a);
		if(temp<t_max && temp>t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p-center)/radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;

}
#endif