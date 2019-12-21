#include<iostream>
#include "vec3.h"

int main(){
	vec3 col(1,2,3);
	vec3 col2(4,5,6);
	col2 -= col;
	// std::cout<<-col2.e[0]<<-col2.e[1]<<-col2.e[2];
	// std::cout<<col2.squared_length();
	std::cout<<col2;
}