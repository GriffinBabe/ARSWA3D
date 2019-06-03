#include "KeyFrame.h"



KeyFrame::KeyFrame()
{
}


KeyFrame::KeyFrame(float timeStamp, std::map<std::string, JointTransform> jointKeyFrames) : timeStamp(timeStamp), pose(jointKeyFrames)
{
}

KeyFrame::~KeyFrame()
{
}
