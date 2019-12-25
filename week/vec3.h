// Vec3 class containing operator overloading for vec3 operations

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3{
public:
	vec3 (){}
	// Constructor for vec class
	float e[3];
	vec3(float e1,float e2,float e3){
		e[0] = e1;
		e[1] = e2;
		e[2] = e3;
	}
	float x()const {
		return e[0];
	}
	float y()const {
		return e[1];

	}
	float z()const {
		return e[2];
	}
	float r()const {
		return e[0];
	}
	float g()const {
		return e[1];

	}
	float b()const {
		return e[2];
	}
	const vec3& operator+()const{
		return *this;
	}
	const vec3 operator-()const{
		return vec3(-e[0],-e[1],-e[2]);
	}
	// overloading e[] operation
	float operator[](int i)const{
		return e[i];
	}
	float& operator[](int i){
		return e[i];
	}
	vec3& operator+=(const vec3 &v2){
		e[0] += v2.e[0];
		e[1] += v2.e[1];
		e[2] += v2.e[2];
	}
	vec3& operator-=(const vec3 &v2){
		e[0] -= v2.e[0];
		e[1] -= v2.e[1];
		e[2] -= v2.e[2];
	}
	vec3& operator*=(const vec3 &v2){
		e[0] *= v2.e[0];
		e[1] *= v2.e[1];
		e[2] *= v2.e[2];
	}
	vec3& operator/=(const vec3 &v2){
		e[0] /= v2.e[0];
		e[1] /= v2.e[1];
		e[2] /= v2.e[2];
	}
	vec3& operator*=(const float t){
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
	}
	vec3& operator/=(const float t){
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
	}

	// vec3& operator+(vec3 &v1,vec3 &v2){
	// 	return vec3(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1]+v1.e[2]+v1.e[2]);
	// }
	
	float length()const{
		return sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
	}
	float squared_length()const{
		return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
	}
	void make_unit_vector(){
		float t = 1.0/(sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]));
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
	}

};
// Dont define these functions within the class ever.
// This one is for input
std::istream& operator>>(std::istream &is, vec3 &t){
		is>>t.e[0]>>t.e[1]>>t.e[2];
		return is;
	}
// This one is for output
std::ostream& operator<<(std::ostream &os, const vec3 &t){
		os<<t.e[0]<<" "<<t.e[1]<<" "<<t.e[2];
		return os;
	}
// This operator overloading is for multiple objects of vec3 class, which is why we cant define
// it within the class
vec3 operator+(const vec3 &v1,const vec3 &v2){
	return vec3(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1],v1.e[2]+v2.e[2]);
}
vec3 operator-(const vec3 &v1,const vec3 &v2){
	return vec3(v1.e[0]-v2.e[0],v1.e[1]-v2.e[1],v1.e[2]-v2.e[2]);
}
vec3 operator*(const vec3 &v1,const vec3 &v2){
	return vec3(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2]);
}
vec3 operator/(const vec3 &v1,const vec3 &v2){
	return vec3(v1.e[0]/v2.e[0],v1.e[1]/v2.e[1],v1.e[2]/v2.e[2]);
}
vec3 operator*(const vec3 &v1,float t){
	return vec3(v1.e[0]*t,v1.e[1]*t,v1.e[2]*t);
}
vec3 operator*(float t,const vec3 &v1){
	return vec3(v1.e[0]*t,v1.e[1]*t,v1.e[2]*t);
}
vec3 operator/(const vec3 &v1,float t){
	return vec3(v1.e[0]/t,v1.e[1]/t,v1.e[2]/t);
}
float dot(const vec3 &v1,const vec3 &v2){
	return v1.e[0]*v2.e[0]+v1.e[1]*v2.e[1]+v1.e[2]*v2.e[2];
}
vec3 cross(const vec3 &v1, const vec3 &v2){
	return vec3(v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1],-(v1.e[0]*v2.e[2]-v1.e[2]*v2.e[1]),v1.e[0]*v2.e[1]-v2.e[0]*v1.e[1]);	
}
vec3 unit_vector(vec3 v){
	return v/v.length();
}