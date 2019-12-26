// This is for bounding volume hierarchies. we divide our space into axis alligned bounding box
// we compute t for which they overlap in 3d(x,y,z). This is also called as 'slab' method
#ifndef AABBH
#define AABBH

#include "ray.h"
// faster than inbuilt fmin and fmax
float ffmin(float a,float b){
	if(a<b){
		return a;
	}
	return b;
}
float ffmax(float a,float b){
	if(a>b){
		return a;
	}
	return b;
}
class aabb{
public:
	// stores 2 vectors ,min and max of the rectangle box. we check if the ray its this slab or not.
	aabb(){}
	vec3 miny;
	vec3 maxy;
	aabb(const vec3& a,const vec3& b){
		miny=a;
		maxy=b;
	}
	vec3 min(){
		return miny;
	}
	vec3 max(){
		return maxy;
	}
	bool hit(const ray& r,float tmin,float tmax)const{
		for(int a=0;a<3;a++){
			float t0 = ffmin((miny[a]-r.origin()[a])/r.direction()[a],
				(maxy[a]-r.origin()[a])/r.direction()[a]);
			float t1 = ffmin((miny[a]-r.origin()[a])/r.direction()[a],
				(maxy[a]-r.origin()[a])/r.direction()[a]);
			tmin = ffmax(t0,tmin);
			tmax = ffmax(t1,tmax);
			if(tmax<=tmin){
				return false;
			}
		}
		return true;
	}
	// Andrew Kensler(Pixar) method for calculation of intersection t
	// bool hit(const ray& r,float tmin,float tmax)const{
	// 	for(int a=0;a<3;a++){
	// 		float invD=1.0/r.direction()[a];
	// 		float t0 = (miny[a]-r.origin()[a])*invD;
	// 		float t1 = (maxy[a]-r.origin()[a])*invD;
	// 		if (invD<0){
	// 			std::swap(t0,t1);
	// 		}
	// 		tmin = ffmax(t0,tmin);
	// 		tmax = ffmax(t1,tmax);
	// 		if(tmax<=tmin){
	// 			return false;
	// 		}
	// 	}
	// 	return true;
	// }

};
// done for motion blur hitables. 
aabb surrounding_box(aabb box0, aabb box1){
	vec3 small(ffmin(box0.min().x(),box1.min().x()), ffmin(box0.min().y(),box1.min().y()),
		ffmin(box0.min().z(),box1.min().z()));
	vec3 big(ffmax(box0.max().x(),box1.max().x()), ffmax(box0.max().y(),box1.max().y()),
		ffmax(box0.max().z(),box1.max().z()));
	return aabb(small,big);
}
#endif