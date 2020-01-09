// We store all the instances of rays hitting the normals and then show selectively
#ifndef HITABLEH
#define HITABLEH

// #include "ray.h"
#include "aabb.h"

// tells the compiler that the pointer is to the class material
class material;
// p is the point where it hits. t is value of t in extrinsic equation of the ray
// normal is the surface normal where the object hits
struct hit_record{
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};
// Now we try to do texture mapping and to do that we map image coordinates to texture coordinates
// this returns the fractional uv for the hittable
void get_sphere_uv(const vec3& p, float& u,float& v){
	float phi = atan2(p.z(),p.x());
	float theta = asin(p.y());
	// normalization
	u = 1-(phi+M_PI)/(2*M_PI);
	v = (theta+M_PI/2)/M_PI;
}
// abstract class. virtual keyword helps in function overriding
// the derived class will overule it
class hitable{
public:
	virtual bool hit(const ray& r, float t_min,float t_max,hit_record& rec) const=0;
	virtual bool bounding_box(float t0,float t1,aabb& box)const=0;
};

#endif