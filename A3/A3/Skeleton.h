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
#include "Bone.h"
#include "Mesh.h"

class Skeleton {
public:
	Bone* rootBone;
	Bone* bones[16];
	int numBones;

	Skeleton();
	void createHand();
};

Skeleton::Skeleton()
{

}

void Skeleton::createHand()
{

}