#ifndef ANIMATION_H
#define ANIMATION_H

#include "KeyFrame.h"
#include <vector>

class Animation
{
private:
	std::vector<KeyFrame> keyFrames;
	float length;

public:

	/**
		@param lengthInSeconds, the total length of the animation
		@param frames, all the keyFrames for the animation
	*/
	Animation(float lengthInSeconds, std::vector<KeyFrame> frames);
	~Animation();

	float getLength() { return length; }
	const std::vector<KeyFrame>& getKeyFrames() { return keyFrames; }
};

#endif ANIMATION_H