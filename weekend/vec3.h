#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3{
public:
	vec3 ();
	// Constructor for vec class
	float e[3];
	vec3(float e1,float e2,float e3){
		e[0] = e1;
		e[1] = e2;
		e[2] = e3;
	};
	float x(){
		return e[0];
	}
	float y(){
		return e[1];

	}
	float z(){
		return e[2];
	}
	float r(){
		return e[0];
	}
	float g(){
		return e[1];

	}
	float b(){
		return e[2];
	}
	const vec3& operator+(){
		return *this;
	}
	const vec3 operator-(){
		return vec3(-e[0],-e[1],-e[2]);
	}
	// overloading e[] operation
	// float operator[](int i){
	// 	return e[i];
	// }
	float& operator[](int i){
		return e[i];
	}
	vec3& operator+=(vec3 &v2){
		e[0] += v2.e[0];
		e[1] += v2.e[1];
		e[2] += v2.e[2];
	}
	vec3& operator-=(vec3 &v2){
		e[0] -= v2.e[0];
		e[1] -= v2.e[1];
		e[2] -= v2.e[2];
	}
	vec3& operator*=(vec3 &v2){
		e[0] *= v2.e[0];
		e[1] *= v2.e[1];
		e[2] *= v2.e[2];
	}
	vec3& operator/=(vec3 &v2){
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
	
	float length(){
		return sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
	}
	float squared_length(){
		return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
	}
	void make_unit_vector(){

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