#include <iostream>
#include<stdlib.h>
#include "vec3.h"
using namespace std;
int main()
{
    int nx = 200;
    int ny = 200;
    // randomize();
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    for(int j=ny-1;j>-1;j--){
        for(int i=0;i<nx;i++){
            // float r = float(rand()%255);
            // float g = float(rand()%255);
            float b = 0.2;
            float r = float(i)/float(nx);
            float g = float(j)/float(ny);
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            vec3 color(ir,ig,ib);
            cout<<color<<"\n";

        }
    }
}