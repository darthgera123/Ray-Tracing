#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cfloat>
// #include "vec3.h"
#include "hitable_list.h"
#include "sphere.h"
// #include "ray.h"
#include "camera.h"
using namespace std;
// Now we compute surface normals and intersect rays with them

vec3 color(const ray &r,hitable *world){
    hit_record rec;
    if(world->hit(r,0,FLT_MAX_EXP,rec)){
        return 0.5*vec3(rec.normal.x()+1,rec.normal.y()+1,rec.normal.z()+1);
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
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            vec3 coly(ir,ig,ib);
            cout<<coly<<"\n";

        }
    }
}