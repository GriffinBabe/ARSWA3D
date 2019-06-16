#ifndef QUATERNION_H

#define QUATERNION_H

#include <glm/glm.hpp>

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	/**
		Converts the Quaternion to a rotation matrix
	*/
	glm::mat4 toRotationMatrix();


	/**
		Interpolates between two quaternions, using the "nlerp" method.
	*/
	static Quaternion interpolate(Quaternion a, Quaternion b, float blend);

	/**
		Extracts the rotation from a transformation matrix and gets the relative Quaternion out of it.
	*/
	static Quaternion fromMatrix(glm::mat4 matrix);

	void normalize();
private:
	float x, y, z, w;
};


#endif // ! QUATERNION_H
