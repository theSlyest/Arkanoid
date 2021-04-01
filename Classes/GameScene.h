//
// Created by Sylvain Kamdem on 30/03/2021.
//

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "Paddle.h"
#include "Ball.h"
#include "Controls.h"
#include "Brick.h"

class GameScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void addScore(uint8_t points);

	void reset();

	void startGame();

	void stopGame();

private:
	static const int8_t BRICKS[3][4];
	Brick* _bricks[3][4];

	uint8_t _score;
	Controls* _controls;
	cocos2d::Label* _scoreLabel;
	cocos2d::MenuItemLabel* _startItem;
	cocos2d::Menu* _menu;
	bool _finished;
	Paddle* _paddle;
	Ball* _ball;

	void checkNode(cocos2d::Node* node);

	void menuStartCallback(cocos2d::Ref* pSender);

	void menuCloseCallback(cocos2d::Ref* pSender);

	bool checkBricks();
};

#endif //_GAME_SCENE_H_
