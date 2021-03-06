#include <iostream>
#include <stdlib.h>
#include <math.h>
// #include "vec3.h"
#include "ray.h"
using namespace std;
// Now we compute surface normals and intersect rays with them
float hit_sphere(const vec3& center,float radius,const ray& r){
    vec3 oc = r.origin()-center;
    float a = dot(r.direction(),r.direction());
    float b = 2*dot(oc,r.direction());
    float c = dot(oc,oc)-radius*radius;
    float discrimiant = b*b-4*a*c;
    // cout<<discrimiant<<" D"<<endl;
    if(discrimiant<0){
        return -1.0;
    }
    else{
        return (-b - sqrt(discrimiant))/(2*a);
    }
}



// check if a sphere intersects with a given ray
bool hitsphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin()-center;
    float a = dot(r.direction(),r.direction());
    float b = 2*dot(oc,r.direction());
    float c = dot(oc,oc)-radius*radius;
    float discrimiant = b*b-4*a*c;
    if(discrimiant>=0.01&&discrimiant<=0.09){
        return true;
    }
    return false;
}

// linear interpolation between white and blue based on position of y
// vec3 color(ray &r){
//     if (hitsphere(vec3(0,0,-1),0.25,r)){
//         return vec3(1,1,0);
//     }
//     if (hitsphere(vec3(1,0,-1),0.5,r)){
//         return vec3(1,0,1);
//     }
//     if (hitsphere(vec3(0,1,-1),0.5,r)){
//         return vec3(0,1,1);
//     }
//     if (hitsphere(vec3(1,1,-2),0.25,r)){
//         return vec3(0,0.5,1);
//     }
//     vec3 unit = unit_vector(r.direction());
//     float t= 0.5*(unit.y()+1.0);
//     return (1-t)*vec3(1,1,1)+t*vec3(0.5,0.7,1);
// }
vec3 color(ray &r){
    // temporary sphere
    vec3 sphere = vec3(-1,0,-1);
    vec3 sphere1 = vec3(1,0,-1);
    float t = hit_sphere(sphere,0.75,r);
    float t2 = hit_sphere(sphere1,0.75,r);
    // cout<<t<<" value"<<"\n";
    if(t>0){
        // Surface normal, we interesect a ray with that and provide a color
        // std::cout<<"Hello";
        vec3 N = unit_vector(r.point_at_parameter(t)-sphere);
        return 0.5*vec3(N.x()+1,N.y()+1,N.z()+1);
    }
    if(t2>0){
        // Surface normal, we interesect a ray with that and provide a color
        // std::cout<<"Hello";
        vec3 N = unit_vector(r.point_at_parameter(t2)-sphere1);
        return 0.5*vec3(N.x()+1,N.y()+1,N.z()+1);
    }
    vec3 unit = unit_vector(r.direction());
    float t1= 0.5*(unit.y()+1.0);
    return (1-t1)*vec3(1,1,1)+t1*vec3(0.5,0.7,1);
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
    // we use a right handed origin system, upward y is +ve, rightward x is +ve. camera is at origin.z = -1
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