//
// Created by Sylvain Kamdem on 30/03/2021.
//

#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"

class Ball : public cocos2d::Sprite {
public:
	static const cocos2d::Vec2 INIT_VELOCITY;
	static const constexpr float VELOCITY_FACTOR = 1.1F;
	static const constexpr int REQ_COLLISIONS = 8;

	static Ball* create(float bottom);

	void hit();

	void start();

	void update(float delta) override;

	void onReachBottom(const std::function<void()> &cb);

private:
	cocos2d::PhysicsBody* _physicsBody;
	int _collisions = 0;
	float _bottom;
	std::function<void()> _onReachBottomCallback;

	bool init(float bottom);
};


#endif //_BALL_H_
