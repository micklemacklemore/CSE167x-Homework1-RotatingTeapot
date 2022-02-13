// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <iostream>
#include "glm/ext.hpp"

// The logic for the functions below is written by me -- Michael Mason
// -------------------------------------------------------------------

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	vec3 norm = glm::normalize(axis);
	double angle = glm::radians(degrees);
	
	// Identity matrix
	mat3 I(1, 0, 0, 0, 1, 0, 0, 0, 1);  
	// axis * axis(transposed)
	mat3 aaT = glm::outerProduct(norm, norm);  
	// A* which is the dual matrix (a.k.a. conjugate transpose, or a hermitian matrix) of axis vector. 
	mat3 A_star = mat3(0, norm.z, -norm.y, -norm.z, 0, norm.x, norm.y, -norm.x, 0); 

	return cos(angle) * I + (1 - cos(angle)) * aaT + sin(angle) * A_star;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	std::cout << "degrees " << degrees << " eye " << glm::to_string(eye) << " up " << glm::to_string(up) << std::endl;
	eye = rotate(degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	std::cout << "degrees " << degrees << " eye " << glm::to_string(eye) << " up " << glm::to_string(up) << std::endl;
	vec3 right = glm::cross(eye, up);
	up = rotate(degrees, right) * up;
	eye = rotate(degrees, right) * eye;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye); // a = eye - center, where center is (0, 0, 0)
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	mat4 uvw(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	mat4 eyeTrans(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1);

	return uvw * eyeTrans;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
