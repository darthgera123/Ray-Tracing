#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cfloat>
// #include "vec3.h"
#include "hitable_list.h"
#include "material.h"
#include "sphere.h"
// #include "ray.h"
#include "camera.h"

using namespace std;


vec3 color(const ray &r,hitable *world,int depth){
    hit_record rec;
    // if(world->hit(r,0,FLT_MAX_EXP,rec)){
    // removal of shadow acne problem by reseting t_min from 0 to 0.001 to remove reflections at t=0.000001
    // shadow acne is self shadowing
    // https://computergraphics.stackexchange.com/questions/2192/cause-of-shadow-acne
    // bias can be modiefied according to slope- results in better removal
    if(world->hit(r,0.001,FLT_MAX_EXP,rec)){
        ray scattered;
        vec3 attenuation;
        // now depth will come into game
        if(depth<20 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
            // cout<<attenuation<<" hello"<<endl;
            return attenuation*color(scattered,world,depth+1);
        }else{
            // shadow
            return vec3(0,0,0);
        }
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
    hitable *list[5];
    list[0] = new sphere(vec3(0,0,-1),0.5,new lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1),100, new lambertian(vec3(0.8,0.8,0)));
    list[2] = new sphere(vec3(1,0,-1),0.5, new metal(vec3(0.8,0.6,0.2),0.3));
    list[3] = new sphere(vec3(-1,0,-1),0.5, new dielectric(1.5));
    // list[4] = new sphere(vec3(-1,-1,-1),-0.45, new dielectric(1.5));
    hitable *world = new hitable_list(list,4);
    vec3 lookfrom(3,2,2);
    vec3 lookat(0,1,-1);
    vec3 up(0,1,0);
    float dist_to_focus = (lookfrom-lookat).length();
    float aperture = 2;
    float fov = 30;
    float aspect = float(nx/ny);
    camera cam(lookfrom,lookat,up,fov,aspect,aperture,dist_to_focus);
    for(int j=ny-1;j>-1;j--){
        for(int i=0;i<nx;i++){
            vec3 col(0,0,0);
            // we take multiple samples of the same pixel and take average of them. 
            // This helps us do antialiasing.
            for(int k=0;k<ns;k++){
                float u = float(i+drand48())/float(nx);
                float v = float(j+drand48())/float(ny);
                ray r = cam.get_ray(u,v);
                col+=color(r,world,0);
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