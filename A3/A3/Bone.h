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
#include "Mesh.h"

using namespace std;

class Bone {
public:
	Bone();
	Bone(string name, Bone* parent, mat4 initial_offset, Mesh joint, Mesh shell, bool hasShell, vec4 jointColour, vec4 shellColour);
	Bone(string name, bool isRoot, mat4 initial_offset, Mesh joint, Mesh shell, bool hasShell, vec4 jointColour, vec4 shellColour);

	void addChild(Bone* child);
	void addChild(string name, mat4 initial_offset, Mesh joint, Mesh shell, bool hasShell);
	void drawBone(mat4 view, mat4 projection);
	void rotateBone();
private:
	bool hasShell;
	bool isRoot;
	Mesh joint;
	Mesh shell;
	vec4 jointColour;
	vec4 shellColour;

	string name;
	Bone* parent;
	vector<Bone> children;
	versor orientation;
	mat4 local_transformation;
	mat4 getGlobalTransformation();
};

Bone::Bone()
{

}

Bone::Bone(string name, Bone* parent, mat4 initial_offset, Mesh joint, Mesh shell = Mesh(), bool hasShell = false, vec4 jointColour = vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4 shellColour = vec4(0.0f, 0.0f, 0.0f, 0.0f))
{
	this->name = name;
	this->isRoot = false;
	this->parent = parent;
	this->local_transformation = initial_offset;
	this->joint = joint;
	this->shell = shell;
	this->hasShell = hasShell;
	this->jointColour = jointColour;
	this->shellColour = shellColour;
}

Bone::Bone(string name, bool isRoot, mat4 initial_offset, Mesh joint, Mesh shell = Mesh(), bool hasShell = false, vec4 jointColour = vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4 shellColour = vec4(0.0f, 0.0f, 0.0f, 0.0f))
{
	this->name = name;
	this->isRoot = isRoot;
	this->parent = NULL;
	this->local_transformation = initial_offset;
	this->joint = joint;
	this->shell = shell;
	this->hasShell = hasShell;
	this->jointColour = jointColour;
	this->shellColour = shellColour;
}

mat4 Bone::getGlobalTransformation()
{
	if (isRoot)
		return local_transformation;
	else
		return parent->getGlobalTransformation() * local_transformation;
}

void Bone::addChild(Bone* child)
{
	this->children.push_back(*child);
}

void Bone::addChild(string name, mat4 initial_offset, Mesh joint, Mesh shell = Mesh(), bool hasShell = false)
{
	Bone child = Bone(name, this, initial_offset, joint, shell, hasShell);
	this->children.push_back(child);
}

void Bone::drawBone(mat4 view, mat4 projection)
{
	mat4 model = getGlobalTransformation();
	joint.drawMesh(view, projection, model, jointColour);
	if (hasShell);
	{
		shell.drawMesh(view, projection, model, shellColour);
	}

	for (GLuint i = 0; i < this->children.size(); i++)
		this->children[i].drawBone(view, projection);
}

void Bone::rotateBone()
{

}