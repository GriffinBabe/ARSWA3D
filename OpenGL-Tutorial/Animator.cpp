#include "Animator.h"

bool Animator::increaseAnimationTime(float delta_time)
{
	animationTime += delta_time;
	if (animationTime > currentAnimation->getLength()) {
		animationTime -= currentAnimation->getLength();
		if (!repeat) {
			return false;
		}
	}
	return true;
}

std::map<std::string, glm::mat4> Animator::calculateCurrentAnimationPose()
{
	std::pair<KeyFrame, KeyFrame> frames = getPreviousAndNextFrame();
	float progression = calculateProgression(frames.first, frames.second);
	return interpolatePoses(frames.first, frames.second, progression);
}

std::pair<KeyFrame, KeyFrame> Animator::getPreviousAndNextFrame()
{
	std::vector<KeyFrame> allFrames = currentAnimation->getKeyFrames();
	KeyFrame previousFrame = allFrames[0];
	KeyFrame nextFrame = allFrames[0];
	for (KeyFrame frame : allFrames) {
		nextFrame = frame;
		if (nextFrame.getTimeStamp() > animationTime) {
			break;
		}
		previousFrame = frame;
	}
	return std::pair<KeyFrame, KeyFrame>(previousFrame, nextFrame);
}

float Animator::calculateProgression(KeyFrame const& previousFrame, KeyFrame const& nextFrame)
{
	float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
	float currentTime = animationTime - previousFrame.getTimeStamp();
	return currentTime / totalTime;
}

std::map<std::string, glm::mat4> Animator::interpolatePoses(const KeyFrame & previousFrame, const KeyFrame & nextFrame, float progression)
{
	std::map<std::string, glm::mat4> currentPose;
	std::map<std::string, JointTransform> previousJoints = previousFrame.getJointKeyFrames();
	std::map<std::string, JointTransform> nextJoints = nextFrame.getJointKeyFrames();

	// Iterating over each keys of the maps.
	for (std::string jointName : extract_keys(previousJoints)) {
		JointTransform previousTransform = previousJoints.at(jointName);
		JointTransform nextTransform = nextJoints.at(jointName);
		JointTransform currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);
		currentPose[jointName] = currentTransform.getLocalTransform();
	}

	return currentPose;
}

void Animator::applyPoseToJoints(std::map<std::string, glm::mat4> const& currentPose, Joint & joint, glm::mat4 const& parentTransform)
{
	glm::mat4 currentLocalTransform = currentPose.at(joint.name);
	glm::mat4 currentTransform = glm::matrixCompMult(parentTransform, currentLocalTransform);
	for (Joint childJoint : joint.children) {
		// Recursively calls the parents
		applyPoseToJoints(currentPose, childJoint, currentTransform);
	}
	currentTransform = glm::matrixCompMult(currentTransform, joint.getInverseBindTransform());
	joint.setAnimationTransform(currentTransform);

}

Animator::Animator()
{
}

Animator::Animator(AnimatedMesh * model)
{
	this->animatedModel = model;
}

void Animator::doAnimation(Animation* animation)
{
	animationTime = 0;
	currentAnimation = animation;
}

void Animator::update(float delta_time)
{
	if (currentAnimation == nullptr)
	{
		return;
	}
	// If we don't want to repeat it and the loop is over, it will return false
	if (increaseAnimationTime(delta_time)) {
		std::map<std::string, glm::mat4> currentPose = calculateCurrentAnimationPose();
	}
	else {

	}
}

Animator::~Animator()
{
}
