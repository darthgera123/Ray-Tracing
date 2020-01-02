#ifndef MATERIALH
#define MATERIALH

#include "hitable.h"
#include "texture.h"
// this computes the random direction the ray would travel after hitting the diffuse surface
vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        p = 2*vec3(drand48(),drand48(),drand48())-vec3(1,1,1);

    }while(p.squared_length()>=1);
    return p;

}

class material{
public:
	// basically it states that after hiting a surface, how much should the ray scatter
	virtual bool scatter(const ray& r_in,const hit_record& rec, vec3& attenuation,ray& scattered)const=0;
};
// here we just make the ray scatter always in some random direction

class lambertian : public material {
    public:
        lambertian(texture *a){
        	albedo=a;
        }
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const  {
        	// pick a random point s from unit radius sphere tangent to the hitpoint(p). Send a ray from hitpoint
        	// to point s. sphere has center at (p+N)? so that random point will be at p+N+s. we send a ray 
        	// in direction of point-p. This somewhat estimates a lambertian surface.
             vec3 target = rec.p + rec.normal + random_in_unit_sphere();
             scattered = ray(rec.p, target-rec.p,r_in.time());
             attenuation = albedo->value(0,0,rec.p);
             return true;
        }

        // vec3 albedo;
        texture *albedo;
};
// returns ray after reflection on a smooth metallic surface
vec3 reflect(const vec3& v, const vec3& n){
	return v-2*dot(v,n)*n;
}

class metal:public material{
public:
	
	metal(const vec3& a,float f){
		albedo =a;
		// right now we have proper reflections, we add fuzz to add randomness to the reflections
		// on the surface. f=1 for avoiding reflections below the surface.
		if(f<1){
			fuzz=1;
		}else{
			fuzz=f;
		}
	}
	virtual bool scatter(const ray& r_in,const hit_record& rec, vec3& attenuation,ray& scattered)const{
		vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
		// scattered = ray(rec.p,reflected+fuzz*random_in_unit_sphere(),r_in.time());
		scattered = ray(rec.p,reflected,r_in.time());
		attenuation = albedo;
		return (dot(scattered.direction(),rec.normal)>0);
	}
	vec3 albedo;
	float fuzz;
};

bool refract(const vec3& v,const vec3 &n,float ni_over_nt,vec3& refracted){
	vec3 uv = unit_vector(v);
	float dt = dot(uv,n);
	float discrimiant = 1 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if(discrimiant>0){
		refracted=ni_over_nt*(uv-n*dt) - n*sqrt(discrimiant);
		return true;
	}
	else{
		return false;
	}
}
// function to approximate reflection at various angles in a dielectric material
float schlick(float cosine,float ref_index){
	float r0 = (1-ref_index)/(1+ref_index);
	r0 *= r0;
	return r0+(1-r0)*pow(1-cosine,5);
}
class dielectric:public material{
public:
	dielectric(float ref){
		ref_index = ref;
	}
	virtual bool scatter(const ray& r_in,const hit_record& rec, vec3& attenuation,ray& scattered)const{
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(),rec.normal);
		float ni_over_nt;
		// glass absorbs nothing. blue channel zero to avoid colour shift
		attenuation = vec3(1,1,1);
		vec3 refracted;
		float reflect_prob;
		float cosine;
		if(dot(r_in.direction(),rec.normal)>0){
			outward_normal = -rec.normal;
			ni_over_nt = ref_index;
			cosine = ref_index * dot(r_in.direction(),rec.normal)/r_in.direction().length();
		}
		else{
			outward_normal = rec.normal;
			ni_over_nt = 1/ref_index;
			cosine = -dot(r_in.direction(),rec.normal)/r_in.direction().length();
		}
		if(refract(r_in.direction(),outward_normal,ni_over_nt,refracted)){
			// scattered = ray(rec.p,refracted);
			reflect_prob = schlick(cosine,ref_index);
		}
		else{
			scattered = ray(rec.p,reflected,r_in.time());
			reflect_prob=1;
			// return false;
		}
		if (drand48()<reflect_prob){
			scattered = ray(rec.p,reflected,r_in.time());
		}
		else{
			scattered = ray(rec.p,refracted,r_in.time());
		}
		return true;
	}
	float ref_index;
};
#endif