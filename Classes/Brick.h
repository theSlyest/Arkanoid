//
// Created by Sylvain Kamdem on 30/03/2021.
//

#ifndef _BRICK_H_
#define _BRICK_H_

#include "cocos2d.h"

class Brick : public cocos2d::Sprite {
public:
	static Brick* create(int8_t hits);

	uint8_t hit();

	int8_t remainingHits() const;

private:
	static const char* SPRITE_NAME;
	int8_t _remainingHits;

protected:
	virtual bool init(int8_t hits);

	virtual std::string getSpriteName() const;
};


#endif //_BRICK_H_
