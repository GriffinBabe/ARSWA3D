#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <map>
#include <string>
#include "JointTransform.h"

/**
	Represents one keyframe of an animation

	Credit to: TheThinMatrix
*/
class KeyFrame
{
private:
	float timeStamp;
	std::map<std::string, JointTransform> pose;


public:
	KeyFrame(float timeStamp, std::map<std::string, JointTransform> jointKeyFrames);
	KeyFrame();
	~KeyFrame();

	/**
		@return The desired bone-space transforms of all the joints at this
	           keyframe, of the animation, indexed by the name of the joint that
	           they correspond to. This basically represents the "pose" at this
	           keyframe.
	*/
	const std::map<std::string, JointTransform>& getJointKeyFrames() const { return pose; }

	float getTimeStamp() const { return timeStamp; }
};

#endif KEYFRAME_H