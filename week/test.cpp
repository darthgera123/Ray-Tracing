#include<iostream>
#include "vec3.h"
class ray{
public:
	// ray();
	vec3 A;
	vec3 B;
	ray(const vec3 a, const vec3 b){
		A=a;
		B=b;
	};
	// vec3 origin()const{
	// 	return A;
	// }
	// vec3 direction()const{
	// 	return B;
	// }
	// vec3 point_at_parameter(float t)const{
	// 	return A+t*B;
	// }
};
// vec3 A;
class Complex{
	public:
		Complex();
		float p[2];
		Complex(float a,float b){
			p[0]=a;
			p[1]=b;
		}
};
class Ray{
public:
	Ray();
	vec3 A;
	Ray(const vec3& a){
		// vec3 Alpha(a.x(),a.y(),a.z());
		A=a;
	}

};

// Ray::Ray():vec3

int main(){
	vec3 col1(1,2,3);
	vec3 col2(4,5,6);
	vec3 col3 =3.5*col2+4*col1;
	// ray r(col1,col2);
	// vec3 col4=col1;
	Ray r(col1);
	// std::cout<<-col2.e[0]<<-col2.e[1]<<-col2.e[2];
	// std::cout<<col2.squared_length();
	// std::cout<<col4;
}