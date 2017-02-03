#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#include <mmsystem.h>
#include <stdio.h>
#include <vector>				// STL dynamic memory
#include <windows.h>

#include "Antons_maths_funcs.h" // Anton's maths functions

using namespace std;

class Bone {
public:
	string name;
	Bone* parent;
	vector<Bone> children;
	versor orientation;
	mat4 local_transformation;
	mat4 getGlobalTransformation();

	Bone();
	Bone(string, Bone* parent);
};

Bone::Bone()
{

}

Bone::Bone(string, Bone* parent)
{

}

mat4 Bone::getGlobalTransformation()
{
	return parent->local_transformation;
}