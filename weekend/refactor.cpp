#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cfloat>
// #include "vec3.h"
#include "hitable_list.h"
#include "sphere.h"
// #include "ray.h"
#include "camera.h"
#include "material.h"
using namespace std;


vec3 color(const ray &r,hitable *world){
    hit_record rec;
    // if(world->hit(r,0,FLT_MAX_EXP,rec)){
    // removal of shadow acne problem by reseting t_min from 0 to 0.001 to remove reflections at t=0.000001
    // shadow acne is self shadowing
    // https://computergraphics.stackexchange.com/questions/2192/cause-of-shadow-acne
    // bias can be modiefied according to slope- results in better removal
    if(world->hit(r,0.001,FLT_MAX_EXP,rec)){
        // return 0.5*vec3(rec.normal.x()+1,rec.normal.y()+1,rec.normal.z()+1);
        // pick a random point s from unit radius sphere tangent to the hitpoint(p). Send a ray from hitpoint
        // to point s. sphere has center at (p+N)? so that random point will be at p+N+s. we send a ray 
        // in direction of point-p. This somewhat estimates a lambertian surface.
        vec3 target = rec.p+ rec.normal+random_in_unit_sphere();
        // only half of color is reflected,therefore its dark
        return 0.5*color(ray(rec.p,target-rec.p),world);
    }
    else{
        vec3 unit = unit_vector(r.direction());
        float t = 0.5*(unit.y()+1);
        return (1.0-t)*vec3(1,1,1) + t*vec3(0.5,0.7,1);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    // randomize();
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1),0.5);
    list[1] = new sphere(vec3(0,-100.5,-1),100);
    hitable *world = new hitable_list(list,2);
    camera cam;
    for(int j=ny-1;j>-1;j--){
        for(int i=0;i<nx;i++){
            vec3 col(0,0,0);
            // we take multiple samples of the same pixel and take average of them. 
            // This helps us do antialiasing.
            for(int k=0;k<ns;k++){
                float u = float(i+drand48())/float(nx);
                float v = float(j+drand48())/float(ny);
                ray r = cam.get_ray(u,v);
                col+=color(r,world);
            }
            col/=float(ns);
            // Sqrt does gamma correction. needed for image viewers.
            int ir = int(255.99*sqrt(col[0]));
            int ig = int(255.99*sqrt(col[1]));
            int ib = int(255.99*sqrt(col[2]));
            vec3 coly(ir,ig,ib);
            cout<<coly<<"\n";

        }
    }
}