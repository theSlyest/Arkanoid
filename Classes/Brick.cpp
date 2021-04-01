//
// Created by Sylvain Kamdem on 30/03/2021.
//

#include "Brick.h"

USING_NS_CC;

const char *Brick::SPRITE_NAME = "brick%d.png";

bool Brick::init(int8_t hits) {
	if (!Sprite::init())
		return false;

	this->_remainingHits = hits;
	this->initWithFile(this->getSpriteName());

	this->_physicsBody = PhysicsBody::createBox(this->getContentSize(),
												PhysicsMaterial(0.F, 1.F, 0.F));
	this->_physicsBody->setDynamic(false);
	this->_physicsBody->setCategoryBitmask(0x02);
	this->_physicsBody->setContactTestBitmask(0x01);
	this->addComponent(this->_physicsBody);
	this->setTag(2);
	this->setUserObject(this);

	return true;
}

Brick *Brick::create(int8_t hits) {
	auto ref = new(std::nothrow) Brick;
	if (ref && ref->init(hits)) {
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

std::string Brick::getSpriteName() const {
	return StringUtils::format(Brick::SPRITE_NAME, this->_remainingHits);
}

uint8_t Brick::hit() {
	if (this->_remainingHits > 1) {
		--this->_remainingHits;
		this->setTexture(this->getSpriteName());
		return 5;
	} else if (this->_remainingHits == 1) {
		this->removeFromParentAndCleanup(false);
		return 10;
	}
	return 0;
}

int8_t Brick::remainingHits() const {
	return this->_remainingHits;
}