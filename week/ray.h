// This is the ray class having functions regarding a simple ray
// ray is defined as p(t)= A+B*t where A is the origin , B is the direction and p is the position along the ray
// t needs to be positive

#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray{
public:
	ray(){}
	vec3 A;
	vec3 B;
	float timey;
	// adding motion blur. it is equivalent to sending random rays through passage of time and averaging
	// the results. the camera moves for some dtime when the aperture is open and rays are sent.
	ray(const vec3& a, const vec3& b, float ti=0.0){
		A=a;
		B=b;
		timey=ti;
	}
	vec3 origin()const{
		return A;
	}
	vec3 direction()const{
		return B;
	}
	float time()const{
		return timey;
	}
	vec3 point_at_parameter(float t)const{
		return A+t*B;
	}
};

#endif