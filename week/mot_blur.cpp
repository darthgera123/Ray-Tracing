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
#include <cstdlib>
using namespace std;


inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

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

hitable *random_scene(){
    int n=500;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,-1000,0),1000,new lambertian(vec3(0.5,0.5,0.5)));
    int i=1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.3,b+0.9*random_double());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.5) {  // diffuse
                    list[i++] = new sphere(
                        center, 0.25,
                        new lambertian(vec3(random_double()*random_double(),
                                            random_double()*random_double(),
                                            random_double()*random_double()))
                    );
                }
                else if (choose_mat < 0.80) { // metal
                    list[i++] = new sphere(
                        center, 0.3,
                        new metal(vec3(0.5*(1 + random_double()),
                                       0.5*(1 + random_double()),
                                       0.5*(1 + random_double())),
                                  0.5*random_double())
                    );
                }
                else if (choose_mat<0.95){  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }else{
                    list[i++] = new sphere(center, -0.2, new dielectric(1.5));   
                }
            }
        }
    }
    list[i++]=new sphere(vec3(0,1,0),1,new dielectric(1.5));
    list[i++]=new sphere(vec3(-4,1,0),1,new lambertian(vec3(0.4,0.2,0.1)));
    list[i++]=new sphere(vec3(4,1,0),1,new metal(vec3(0.7,0.6,0.2),0));
    return new hitable_list(list,i);
}
hitable *random_scene_mot_blur(){
    int n=500;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,-1000,0),1000,new lambertian(vec3(0.5,0.5,0.5)));
    int i=1;
    for (int a = -4; a < 4; a++) {
        for (int b = -4; b < 4; b++) {
            float choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.3,b+0.9*random_double());
            if ((center-vec3(4,0.3,0)).length() > 0.9) {
                if (choose_mat < 0.7) {  // diffuse
                    list[i++] = new moving_sphere(
                        center, center+vec3(0,0.5*random_double(),0),0,1,0.25,
                        new lambertian(vec3(random_double()*random_double(),
                                            random_double()*random_double(),
                                            random_double()*random_double()))
                    );
                }
                else if (choose_mat < 0.80) { // metal
                    list[i++] = new sphere(
                        center, 0.3,
                        new metal(vec3(0.5*(1 + random_double()),
                                       0.5*(1 + random_double()),
                                       0.5*(1 + random_double())),
                                  0.5*random_double())
                    );
                }
                else if (choose_mat<0.95){  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }else{
                    list[i++] = new sphere(center, -0.2, new dielectric(1.5));   
                }
            }
        }
    }
    list[i++]=new sphere(vec3(4,1,0),1,new dielectric(1.5));
    list[i++]=new sphere(vec3(-4,1,0),1,new lambertian(vec3(0.4,0.2,0.1)));
    list[i++]=new sphere(vec3(0,1,0),1,new metal(vec3(0.7,0.6,0.2),0));
    return new hitable_list(list,i);
}
int main()
{
    int nx = 1000;
    int ny = 800;
    int ns = 40;
    // randomize();
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    // hitable *list[5];
    // list[0] = new sphere(vec3(0,0,-1),0.5,new lambertian(vec3(0.8,0.3,0.3)));
    // list[1] = new sphere(vec3(0,-100.5,-1),100, new lambertian(vec3(0.8,0.8,0)));
    // list[2] = new sphere(vec3(1,0,-1),0.5, new metal(vec3(0.8,0.6,0.2),0.3));
    // list[3] = new sphere(vec3(-1,0,-1),0.5, new dielectric(1.5));
    // // list[4] = new sphere(vec3(-1,-1,-1),-0.45, new dielectric(1.5));
    hitable *world = random_scene_mot_blur();
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,1,-1);
    vec3 up(0,1,0);
    // float dist_to_focus = (lookfrom-lookat).length();
    float dist_to_focus=10;
    float aperture = 0.1;
    float fov = 40;
    float aspect = float(nx/ny);
    camera cam(lookfrom,lookat,up,fov,aspect,aperture,dist_to_focus,0,1);
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