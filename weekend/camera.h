#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

vec3 random_in_unit_disk(){
	vec3 p;
	do{
		p=2*vec3(drand48(),drand48(),drand48()) - vec3(1,1,0);
	}while(dot(p,p)>=1);
	return p;
}
class camera{
public:
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
	float lens_radius;
	vec3 u,v,w;
	// vertical field of view - top to bottom in degrees
	camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float aperture,float focus_dist){
		// we use a right handed origin system, upward y is +ve, rightward x is +ve. camera is at origin.z = -1
		lens_radius = aperture/2;
		float theta = vfov*M_PI/180;
		float half_height = tan(theta/2);
		float half_width = aspect*half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom-lookat);
		u = unit_vector(cross(vup,w));
		v = cross(w,u);
		// now we are using a lens since this is not a pinhole so for all rays to behave like one
		// we use depth of field or motion blur.
		lower_left_corner = origin-half_width*u*focus_dist - half_width*v*focus_dist -focus_dist*w;
		horizontal= 2*half_width*u*focus_dist;
		vertical = 2*half_height*v*focus_dist;

		// horizontal = vec3(2*half_width,0,0);
		// vertical = vec3(0,2*half_height,0);
		// origin = vec3(0,0,0);
	}
	ray get_ray(float s,float t){
		vec3 rd = lens_radius*random_in_unit_disk();
		vec3 offset = u*rd.x()+v*rd.y();
		return ray(origin+offset,lower_left_corner+s*horizontal+t*vertical-origin-offset);
	}
};

#endif