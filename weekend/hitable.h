// We store all the instances of rays hitting the normals and then show selectively
#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record{
	float t;
	vec3 p;
	vec3 normal;
};
// abstract class. virtual keyword helps in function overriding
// the derived class will overule it
class hitable{
public:
	virtual bool hit(const ray& r, float t_min,float t_max,hit_record& rec) const=0;
};

#endif