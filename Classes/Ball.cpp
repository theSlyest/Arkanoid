//
// Created by Sylvain Kamdem on 30/03/2021.
//

#include "Ball.h"

USING_NS_CC;

const Vec2 Ball::INIT_VELOCITY = Vec2(80.F, 180.F);

bool Ball::init(float bottom) {
	if (!Sprite::init())
		return false;

	this->_bottom = bottom;
	this->initWithFile("ballGrey.png");
	this->_physicsBody = PhysicsBody::createCircle(this->getContentSize().width / 2.F,
												   PhysicsMaterial(0.F, 1.F, 0.F));
	this->_physicsBody->setGravityEnable(false);
	this->_physicsBody->setDynamic(true);
	this->_physicsBody->setCategoryBitmask(0x01);
	this->_physicsBody->setContactTestBitmask(0x02);
	this->addComponent(this->_physicsBody);
	this->setTag(1);
	this->setUserObject(this);

	return true;
}

Ball *Ball::create(float bottom) {
	auto ref = new(std::nothrow) Ball;
	if (ref && ref->init(bottom)) {
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

void Ball::hit() {
	++this->_collisions;
//	cocos2d::log("Ball collisions = %d", this->_collisions);
	if (this->_collisions == Ball::REQ_COLLISIONS) {
		this->_collisions = 0;
		this->_physicsBody->setVelocity(this->_physicsBody->getVelocity() * Ball::VELOCITY_FACTOR);
//		cocos2d::log("Ball velocity changed");
	}
}

void Ball::start()
{
	this->_physicsBody->setVelocity(Ball::INIT_VELOCITY);
}

void Ball::update(float delta) {
	Node::update(delta);
	if (this->getPositionY() < this->_bottom) {
		this->_physicsBody->setVelocity(Vec2::ZERO);
		if (this->_onReachBottomCallback)
			this->_onReachBottomCallback();
	}
}

void Ball::onReachBottom(const std::function<void()> &cb) {
	this->_onReachBottomCallback = cb;
}