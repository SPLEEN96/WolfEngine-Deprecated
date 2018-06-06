#pragma once
//Values taken from http://devernay.free.fr/cours/opengl/materials.html
#include "Texture.h"

#include "..\Core\Math\Vector.h"


struct Material {
	Material(const Vector3f &ambient, const Vector3f &diffuse, const Vector3f &specular, const float &shininess, Texture* texture=NULL)
		:Ambient(ambient),
		Diffuse(diffuse),
		Specular(specular),
		Shininess(shininess),
	    Texture(texture) {}
	Material(const Material &rhs, Texture* texture=NULL)
		:Ambient(rhs.Ambient),
		Diffuse(rhs.Diffuse),
		Specular(rhs.Specular),
		Shininess(rhs.Shininess),
		Texture(texture){}
	


	const Vector3f Ambient;
	const Vector3f Diffuse;
	const Vector3f Specular;
	const float Shininess;
	Texture *Texture;
};



static Material MAT_WHITE(Vector3f(1.f), Vector3f(1.f), Vector3f(0.332741f, 0.328634f, 0.346435f), 128.f*0.3f);
static Material MAT_EMERALD(Vector3f(0.0215f, 0.1745f, 0.0215f), Vector3f(0.07568f, 0.61424f, 0.07568f), Vector3f(0.663f, 0.727811f, 0.633f), 128.f*0.6f);
static Material MAT_OBSIDIAN(Vector3f(0.05375f, 0.05f, 0.06625f), Vector3f(0.18275f, 0.17f, 0.22525f), Vector3f(0.332741f, 0.328634f, 0.346435f), 128.f*0.3f);
static Material MAT_RUBY(Vector3f(0.1745f, 0.01175f, 0.01175f), Vector3f(0.61424f, 0.04136f, 0.04136f), Vector3f(0.727811f, 0.626959f, 0.626959f), 128.f*0.6f);
