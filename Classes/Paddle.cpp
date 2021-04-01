//
// Created by Sylvain Kamdem on 30/03/2021.
//

#include "Paddle.h"
#include "PhysicsBodyParser.h"

USING_NS_CC;

bool Paddle::init() {
	if (!Sprite::init())
		return false;

	this->initWithFile("paddleBlu.png");
	this->_moving = false;
	this->_right = false;

//	auto physicsBody = PhysicsBody::createBox(this->getContentSize(),
//											  PhysicsMaterial(0.F, 1.F, 0.F));
	PhysicsBodyParser::getInstance()->parseJsonFile("paddle.json");
	auto physicsBody = PhysicsBodyParser::getInstance()->bodyFromJson(this, "paddleBlu.png",
															   PhysicsMaterial(0.F, 1.F, 0.F));
	physicsBody->setDynamic(false);
	this->addComponent(physicsBody);
	PhysicsBodyParser::getInstance()->clearCache();
	return true;
}

Paddle *Paddle::create() {
	auto ref = new(std::nothrow) Paddle;
	if (ref && ref->init()) {
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

void Paddle::setDirection(bool right) {
	this->_right = right;
}

void Paddle::start() {
	this->scheduleUpdate();
}

void Paddle::update(float delta) {
	Node::update(delta);
	float x = this->getPositionX() + (this->_right ? 1.F : -1.F) * Paddle::VELOCITY * delta;
	if (98.F <= x && x <= 442.F)
		this->setPosition(x, this->getPositionY());
}

void Paddle::stop() {
	this->unscheduleUpdate();
}
