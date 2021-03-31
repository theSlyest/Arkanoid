//
// Created by Sylvain Kamdem on 31/03/2021.
//

#include "WallBlock.h"

USING_NS_CC;

bool WallBlock::init() {
	if (!Sprite::init())
		return false;

	this->initWithFile("greySquare.png");

	return true;
}

WallBlock *WallBlock::create() {
	auto ref = new(std::nothrow) WallBlock;
	if (ref && ref->init()) {
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}