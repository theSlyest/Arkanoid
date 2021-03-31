//
// Created by Sylvain Kamdem on 31/03/2021.
//

#ifndef _WALL_BLOCK_H_
#define _WALL_BLOCK_H_

#include "cocos2d.h"

class WallBlock : public cocos2d::Sprite {
public:
	static WallBlock* create();

private:
	bool init();

};


#endif //_WALL_BLOCK_H_
