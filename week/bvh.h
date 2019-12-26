#ifndef BVHH
#define BVHH
#include "hitable.h"

// pointing to the root node
class bvh_node:public hitable{
public:
	hitable *left;
	hitable *right;
	aabb box;
	bvh_node(){}
	bvh_node(hitable **l,int n,float t0,float t1);
	virtual bool hit(const ray& r,float tmin,float tmax,hit_record& rec)const;
	virtual bool bounding_box(float t0,float t1,aabb& b)const;
};
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// This is the most crucial part of the ray tracer. it involves splitting of the nodes
// we want to ensure this happens efficiently and splitting is done well. SO we choose a random axis
// then sort them and put half in each subtree.

bool bvh_node::bvh_node(hitable **l,int n,float time0,float time1){
	int axis = int(3*random_double());
}


bool bvh_node::bounding_box(float t0,float t1,aabb& b)const{
	b=box;
	return true;
}

// checking for child nodes recursively if it hits in that. if it hits any one child node then it hits parent node
bool bvh::hit(const ray& r,float tmin,float tmax,hit_record& rec)const{
	if(box.hit(r,tmin,tmax)){
		hit_record left_rec,right_rec;
		bool hit_left = left->hit(r,tmin,tmax,left_rec);
		bool hit_right = right->hit(r,tmin,tmax,right_rec);
		if(hit_left && hit_right){
			if(left_rec.t<right_rec.t){
				rec=left_rec;
			}else{
				rec = right_rec;
			}
			return true;
		}
		else if(hit_left){
			rec=left_rec;
			return true;
		}else if(hit_right){
			rec = right_rec;
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}
#endif