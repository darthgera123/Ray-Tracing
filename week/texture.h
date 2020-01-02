#ifndef TEXTUREH
#define TEXTUREH
// #include "vec3.h"

// now we treat colors as solid texture which will be changed everywhere
class texture{
public:
	virtual vec3 value(float u,float v,const vec3& p)const=0;
};

class constant_texture:public texture{
public:
	constant_texture(){}
	vec3 color;
	constant_texture(vec3 c){
		color =c;
	}
	virtual vec3 value(float u,float v,const vec3& p)const{
		return color;
	}
};
// constructing checkered texture using sines and cosines. if we multiply trig functions in all 3 dim
/*the sign of the product forms a 3d checkered pattern.Pat Hanrahan 1980*/
class checker_texture:public texture{
public:
	checker_texture(){}
	texture *even,*odd;
	checker_texture(texture *t0,texture *t1){
		even=t0;
		odd =t1;
	}
	virtual vec3 value(float u,float v,const vec3& p)const{
		float sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
		if(sines<0)
			return odd->value(u,v,p);
		else
			return even->value(u,v,p); 
	}
};

#endif