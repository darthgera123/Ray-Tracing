#include <iostream>
#include <stdlib.h>
// #include "vec3.h"
#include "ray.h"
using namespace std;

// linear interpolation between white and blue based on position of y
vec3 color(ray &r){
    vec3 unit = unit_vector(r.direction());
    float t= 0.5*(unit.y()+1.0);
    return (1-t)*vec3(1,1,1)+t*vec3(0.5,0.7,1);
}
int main()
{
    int nx = 200;
    int ny = 100;
    // randomize();
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    vec3 lower_left_corner(-2,-1,-1);
    vec3 horizontal(4,0,0);
    vec3 vertical(0,2,0);
    // we use a right handed origin system, upward y is +ve, rightward x is +ve. camera is at origin
    vec3 origin(0,0,0);
    for(int j=ny-1;j>-1;j--){
        for(int i=0;i<nx;i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            vec3 direction = lower_left_corner+u*horizontal+v*vertical;
            // direction is a unit vector.
            direction = unit_vector(direction);
            ray r(origin,direction);

            vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            vec3 coly(ir,ig,ib);
            cout<<coly<<"\n";

        }
    }
}