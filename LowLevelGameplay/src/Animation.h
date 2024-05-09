#pragma once
#include <vector>
#include <memory>
#include <Vector2.h>
#include <iostream>
#include <Object.h>

class Animation : public Object
{
public:
#pragma region Constructors & Destructors
	Animation(std::vector<LLGP::Vector2i> animationPos);
	Animation(std::vector<LLGP::Vector2i> animationPos, int animationType);
	Animation();
	~Animation();
#pragma endregion

#pragma region Notes To Self/Old Implementation of Variadic Templates
	//Trial variadic template, attempting to add animations by repeated insertion of vector2's;
	//I realised I didn't need to template variables as I'd only ever have Vector2i's.
	//template<class... Types>
	//void addAnimation(Types... newAnimPosition)
	//{
	//	addAnimationFrame(newAnimPosition...);
	//}
#pragma endregion

	//Used to retrieve and iterate the next frame of the animation
	LLGP::Vector2i getNextFrame();


	//I have swapped to Variadic args.
	void addAnimation(int numArgs, ...);

	//Just reset the animation, to be called when we swap from one animation to another.
	inline void resetAnim() { currentFrame = -1; }

	inline void clearAnim() { animationPositions.get()->clear(); }

	//This is created so that I can differentiate from the multiple animations present in each
	//animation state.
	inline void setName(std::string newName) { m_animName = newName; }
	inline std::string getName() { return m_animName; }

protected:

	std::shared_ptr<std::vector<LLGP::Vector2i>> animationPositions;
	bool largeAnim;
	std::shared_ptr<std::vector<LLGP::Vector2i>> animationSizes;
	//bool uniqueAnim;
	//std::unique_ptr<LLGP::Vector2i> animationOrigin;
	int currentFrame;
	int animType;
	std::string m_animName;
private:
	inline void addAnimationFrame(LLGP::Vector2i framePosition);
};
