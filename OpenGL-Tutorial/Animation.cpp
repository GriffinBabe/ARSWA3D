#include "Animation.h"


Animation::Animation()
{
}

Animation::Animation(float lengthInSeconds, std::vector<KeyFrame> frames)
{
	length = lengthInSeconds;
	keyFrames = frames;
}

Animation::~Animation()
{
}
