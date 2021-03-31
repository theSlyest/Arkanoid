//
// Created by Sylvain Kamdem on 30/03/2021.
//

#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"

class Paddle : public cocos2d::Sprite {
public:
	static const constexpr float VELOCITY = 128.F;
	static const constexpr float LOW_VELOCITY = 96.F;

	static Paddle* create();

	void setDirection(bool right);

	void start();

	void stop();

	void update(float delta) override;

private:
	bool init() override;
	bool _right;
	bool _moving;
};


#endif //_PADDLE_H_
