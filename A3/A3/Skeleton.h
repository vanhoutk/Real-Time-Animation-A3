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
	void createHand(Mesh handMesh, Mesh handShell, Mesh jointMesh, Mesh jointShell, Mesh tipMesh, Mesh tipShell);
	void drawSkeleton(mat4 view, mat4 projection);
};

Skeleton::Skeleton()
{

}

void Skeleton::createHand(Mesh handMesh, Mesh handShell, Mesh jointMesh, Mesh jointShell, Mesh tipMesh, Mesh tipShell)
{
	vec4 joint_colour = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	vec4 shell_colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	bones[0] = new Bone("hand", true, identity_mat4(), handMesh, Mesh(), false, joint_colour, shell_colour);
	rootBone = bones[0];

	// Thumb
	mat4 thumb1_local = translate(rotate_y_deg(scale(identity_mat4(), vec3(0.75f, 1.0f, 1.0f)), 30.0f), vec3(3.0f, 0.0f, 2.5f));
	bones[1] = new Bone("thumb_1", bones[0], thumb1_local, jointMesh, jointShell, true, joint_colour, shell_colour);
	
	mat4 thumb2_local = translate(rotate_y_deg(identity_mat4(), -5.0f), vec3(-5.0f, 0.0f, 0.0f));
	bones[2] = new Bone("thumb_2", bones[1], thumb2_local, jointMesh, jointShell, true, joint_colour, shell_colour);
	
	mat4 thumb3_local = translate(rotate_y_deg(identity_mat4(), -10.0f), vec3(-5.0f, 0.0f, 0.0f));
	bones[3] = new Bone("thumb_3", bones[2], thumb3_local, tipMesh, tipShell, true, joint_colour, shell_colour);
	
	bones[2]->addChild(bones[3]);
	bones[1]->addChild(bones[2]);
	bones[0]->addChild(bones[1]);

	// Finger 1
	mat4 finger11_local = translate(scale(identity_mat4(), vec3(0.9f, 0.9f, 0.9f)), vec3(-4.0f, 0.0f, 3.1f));
	bones[4] = new Bone("finger_11", bones[0], finger11_local, jointMesh, jointShell, true, joint_colour, shell_colour);

	mat4 finger_joint_offset = translate(identity_mat4(), vec3(-5.0f, 0.0f, 0.0f));
	bones[5] = new Bone("finger_12", bones[4], finger_joint_offset, jointMesh, jointShell, true, joint_colour, shell_colour);
	
	bones[6] = new Bone("finger_13", bones[5], finger_joint_offset, tipMesh, tipShell, true, joint_colour, shell_colour);
	
	bones[5]->addChild(bones[6]);
	bones[4]->addChild(bones[5]);
	bones[0]->addChild(bones[4]);

	// Finger 2
	mat4 finger21_local = translate(identity_mat4(), vec3(-4.0f, 0.0f, 0.9f));
	bones[7] = new Bone("finger_21", bones[0], finger21_local, jointMesh, jointShell, true, joint_colour, shell_colour);

	bones[8] = new Bone("finger_22", bones[7], finger_joint_offset, jointMesh, jointShell, true, joint_colour, shell_colour);

	bones[9] = new Bone("finger_23", bones[8], finger_joint_offset, tipMesh, tipShell, true, joint_colour, shell_colour);
	
	bones[8]->addChild(bones[9]);
	bones[7]->addChild(bones[8]);
	bones[0]->addChild(bones[7]);

	// Finger 3
	mat4 finger31_local = translate(scale(identity_mat4(), vec3(0.9f, 0.9f, 0.9f)), vec3(-4.0f, 0.0f, -1.3f));
	bones[10] = new Bone("finger_31", bones[0], finger31_local, jointMesh, jointShell, true, joint_colour, shell_colour);
	
	bones[11] = new Bone("finger_32", bones[10], finger_joint_offset, jointMesh, jointShell, true, joint_colour, shell_colour);

	bones[12] = new Bone("finger_33", bones[11], finger_joint_offset, tipMesh, tipShell, true, joint_colour, shell_colour);
	
	bones[11]->addChild(bones[12]);
	bones[10]->addChild(bones[11]);
	bones[0]->addChild(bones[10]);

	// Finger 4
	mat4 finger41_local = translate(scale(identity_mat4(), vec3(0.7f, 0.7f, 0.7f)), vec3(-4.0f, 0.0f, -3.1f));
	bones[13] = new Bone("finger_41", bones[0], finger41_local, jointMesh, jointShell, true, joint_colour, shell_colour);

	bones[14] = new Bone("finger_42", bones[13], finger_joint_offset, jointMesh, jointShell, true, joint_colour, shell_colour);

	bones[15] = new Bone("finger_43", bones[14], finger_joint_offset, tipMesh, tipShell, true, joint_colour, shell_colour);
	
	bones[14]->addChild(bones[15]);
	bones[13]->addChild(bones[14]);
	bones[0]->addChild(bones[13]);
}

void Skeleton::drawSkeleton(mat4 view, mat4 projection)
{
	rootBone->drawBone(view, projection);
}