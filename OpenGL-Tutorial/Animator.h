#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Animation.h"
#include "Joint.h"

class AnimatedMesh;

/**
	This class contains all the functionalities to apply the animation to an AnimatedMesh.
	It also keeps track of the running time and a reference to the animation that currently
	gets played.

	The animator needs to be updated every frame to get the time updated.
	The current animation can be played anythime trough the doAnimation() method.
	The current animation gets looped until we change it. But we can also chose to play it
	only one time.

	The Animator calculates the desired current animation pose by interpolating
	between the previous and next keyframes of the animation (based on the
	current animation time). The Animator then updates the transforms all of the
	joints each frame to match the current desired animation pose.

	Credit To: TheThinMatrix
*/
class Animator
{

private:
	bool repeat = true;
	AnimatedMesh* animatedModel = nullptr;
	Animation* currentAnimation = nullptr;
	float animationTime = 0;

	/**
		Increase the time and resets it when it has done the whole animation time.
		Causing it to loop.
		
		@param delta_time, the time that passed since the last game loop.
	
		@return if the loop has been crossed. It's usefull to stop the animation when you don't want it to repeat
	*/
	bool increaseAnimationTime(float delta_time);


	/**
		This method calculates the current pose. It will get between which timestamp we are and will interpolate
		the rig between those two timstamps.

		@return the current map with the bone name as key and it's transformation matrix.
	*/
	std::map<std::string, glm::mat4> calculateCurrentAnimationPose();

	/**
		Gets between each frames we are according to time

		E.g.:

		f1    f2    f3
		|-----|-----|	We are between f1 and f2
		   ^
	*/
	std::pair<KeyFrame, KeyFrame> getPreviousAndNextFrame();

	/**
		Calculates how far between the previous and next keyFrame the current animation is.
		@return a value between 0 and 1 and will be used for interpolation.
	*/
	float calculateProgression(KeyFrame const& previousFrame, KeyFrame const& nextFrame);

	/**
		Calculates the location and rotation of each joint by interpolating between the two keyFrames we currently are.

		NB: The interpolation is linear

		@param previousFrame
			- the preivous KeyFrame in the animation
		@param nextFrame
			- the nextFrame in the animation
		@param progression
			- float value between 0 and 1, represents where we are between the two given frames.
	*/
	std::map<std::string, glm::mat4> interpolatePoses(const KeyFrame& previousFrame, const KeyFrame& nextFrame, float progression);

	/**
		The animator calculates and sets the joint transforms.
	*/
	void applyPoseToJoints(std::map<std::string, glm::mat4> const& currentPose, Joint& joint, glm::mat4 const& parentTransform);


	/**
		Utility function to extracts all the key names from the std::map<std::string, glm::mat4> maps we use in our methods.
	*/
	template<typename TK, typename TV>
	std::vector<TK> extract_keys(std::map<TK, TV> const& input_map);


public:
	Animator();
	Animator(AnimatedMesh* model);

	/**
		Changes the animation to be played and resets the animation time.
	*/
	void doAnimation(Animation* animation);


	void update(float delta_time);
	~Animator();
};

template<typename TK, typename TV>
inline std::vector<TK> Animator::extract_keys(std::map<TK, TV> const & input_map)
{
	std::vector<TK> retval;
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
}

#endif
