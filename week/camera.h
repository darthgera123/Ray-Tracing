#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "random.h"

vec3 random_in_unit_disk(){
	vec3 p;
	do{
		p=2*vec3(random_double(),random_double(),random_double()) - vec3(1,1,0);
	}while(dot(p,p)>=1);
	return p;
}
// class camera{
// public:
// 	vec3 lower_left_corner;
// 	vec3 horizontal;
// 	vec3 vertical;
// 	vec3 origin;
// 	float lens_radius;
// 	vec3 u,v,w;
// 	float time0;
// 	float time1;
// 	// vertical field of view - top to bottom in degrees
// 	// t0 and t1 are for motion blur
// 	camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float aperture,float focus_dist,float t0,float t1){
// 		// we use a right handed origin system, upward y is +ve, rightward x is +ve. camera is at origin.z = -1
// 		time0 = t0;
// 		time1 = t1;
// 		lens_radius = aperture/2;
// 		float theta = vfov*M_PI/180;
// 		float half_height = tan(theta/2);
// 		float half_width = aspect*half_height;
// 		origin = lookfrom;
// 		w = unit_vector(lookfrom-lookat);
// 		u = unit_vector(cross(vup,w));
// 		v = cross(w,u);
// 		// now we are using a lens since this is not a pinhole so for all rays to behave like one
// 		// we use depth of field or motion blur.
// 		lower_left_corner = origin-half_width*u*focus_dist - half_width*v*focus_dist -focus_dist*w;
// 		horizontal= 2*half_width*u*focus_dist;
// 		vertical = 2*half_height*v*focus_dist;

// 		// horizontal = vec3(2*half_width,0,0);
// 		// vertical = vec3(0,2*half_height,0);
// 		// origin = vec3(0,0,0);
// 	}
// 	// new: add time to comstruct ray
// 	ray get_ray(float s,float t){
// 		vec3 rd = lens_radius*random_in_unit_disk();
// 		vec3 offset = u*rd.x()+v*rd.y();
// 		float time = time0+drand48()*(time1-time0);
// 		return ray(origin+offset,lower_left_corner+s*horizontal+t*vertical-origin-offset,time);
// 	}
// };
class camera {
    public:
        // new:  add t0 and t1
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist, float t0, float t1) { // vfov is top to bottom in degrees
            time0 = t0;
            time1 = t1;
            lens_radius = aperture / 2;
            float theta = vfov*M_PI/180;
            float half_height = tan(theta/2);
            float half_width = aspect * half_height;
            origin = lookfrom;
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);
            lower_left_corner = origin  - half_width*focus_dist*u -half_height*focus_dist*v - focus_dist*w;
            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;
        }

        // new: add time to construct ray
        ray get_ray(float s, float t) {
            vec3 rd = lens_radius*random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();
            float time = time0 + random_double()*(time1-time0);
            return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset, time); 
        }

        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        float time0, time1;  // new variables for shutter open/close times
        float lens_radius;
};
#endif