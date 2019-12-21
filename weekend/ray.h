// This is the ray class having functions regarding a simple ray
// ray is defined as p(t)= A+B*t where A is the origin , B is the direction and p is the position along the ray
// t needs to be positive

#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray{
public:
	ray();
	vec3 A;
	vec3 B;
	ray(const vec3& a, const vec3& b){
		A=a;
		B=b;
	}
	vec3 origin()const{
		return A;
	}
	vec3 direction()const{
		return B;
	}
	vec3 point_at_parameter(float t)const{
		return A+t*B;
	}
};

#endif