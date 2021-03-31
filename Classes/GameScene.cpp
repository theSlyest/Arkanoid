//
// Created by Sylvain Kamdem on 30/03/2021.
//

#include "GameScene.h"
#include "WallBlock.h"

USING_NS_CC;

const int8_t GameScene::BRICKS[3][4] = {{0, 1, 2, 1},
										{1, 2, 2, 0},
										{0, 0, 1, 2}};

Scene *GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::initWithPhysics())
		return false;

	this->_finished = false;
	this->getPhysicsWorld()->setGravity(Vec2(0.F, 0.F));

	// optional: enable debug draw
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float midX = visibleSize.width / 2;
	float midY = visibleSize.height / 2;

	float squareSize = 32.F;
	int squares = 16;
	float top = midY + squareSize * 8.F;
	float bottom = top + 10.F - static_cast<float>(squares) * squareSize;
	float left = 30.F;
	float right = visibleSize.width - 30.F;
	float x;

	auto bg = LayerColor::create(Color4B(28, 50, 105, 255));
	float xHalf = squareSize * 7.F;
	float yHalf = squareSize * 7.5F;
	Vec2 points[] = {
			Vec2(-xHalf, -yHalf),
			Vec2(-xHalf, yHalf),
			Vec2(xHalf, yHalf),
			Vec2(xHalf, -yHalf)
	};
	auto edge = PhysicsBody::createEdgeChain(points, 4, PhysicsMaterial(0.F, 1.F, 0.F));
	bg->addComponent(edge);
	this->addChild(bg);

	WallBlock *square;
	Sprite *dot;
	// Upper wall and bottom line
	for (int i = 0; i < 16; ++i) {
		x = left + squareSize * static_cast<float>(i);
		square = WallBlock::create();
		square->setPosition(x, top);
		this->addChild(square);
		dot = Sprite::create("dot.png");
		dot->setPosition(x, bottom);
		this->addChild(dot);
	}

	// Side walls
	for (int i = 1; i < 16; ++i) {
		square = WallBlock::create();
		square->setPosition(left, top - squareSize * static_cast<float>(i));
		this->addChild(square);
		square = WallBlock::create();
		square->setPosition(right, top - squareSize * static_cast<float>(i));
		this->addChild(square);
	}

	this->paddle = Paddle::create();
	this->paddle->setPosition(midX, bottom + 18.F);
	this->addChild(this->paddle);
	this->paddle->unscheduleUpdate();

	this->ball = Ball::create(bottom);
	this->ball->setPosition(midX, this->paddle->getPositionY() + 23.F);
	this->ball->onReachBottom([this]() {
		this->stopGame();
	});
	this->addChild(this->ball);

	top -= 128.F;
	left += 144.F;
	for (int l = 0; l < 3; ++l) {
		for (int c = 0; c < 4; ++c) {
			this->_bricks[l][c] = Brick::create(GameScene::BRICKS[l][c]);
			this->_bricks[l][c]->setPosition(midX + (c - 1.5F) * 64.F, top - l * 32.F);
			this->addChild(this->_bricks[l][c]);
		}
	}

	this->_score = 0;
	this->_scoreLabel = Label::createWithTTF("0000", "fonts/Marker Felt.ttf", 32.F);
	this->_scoreLabel->setPosition(midX, 840.F);
	this->addChild(this->_scoreLabel);

	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
										   CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	closeItem->setPosition(500.F, 920.F);
	this->_startItem = MenuItemLabel::create(
			Label::createWithTTF("TOUCH TO START", "fonts/Marker Felt.ttf", 48.F),
			CC_CALLBACK_1(GameScene::menuStartCallback, this));
	this->_startItem->setPosition(midX, 120.F);
	this->_menu = Menu::create(closeItem, this->_startItem, nullptr);
	this->_menu->setPosition(Vec2::ZERO);
	this->addChild(this->_menu);

	this->_controls = new Controls(this);
	this->_controls->onKeyPressed([this](bool right) {
		this->paddle->setDirection(right);
		this->paddle->start();
	});

	this->_controls->onTouch([this](const Vec2 &location) {
		if (location.x != this->paddle->getPositionX()) {
			this->paddle->setDirection(location.x > this->paddle->getPositionX());
			this->paddle->start();
		}
	});

	this->_controls->onRelease([this]() {
		this->paddle->stop();
	});

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactSeparate = [this](PhysicsContact &contact) {
		this->checkNode(contact.getShapeA()->getBody()->getOwner());
		this->checkNode(contact.getShapeB()->getBody()->getOwner());
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void GameScene::checkNode(cocos2d::Node *node) {
	uint8_t points;
	switch (node->getTag()) {
		case 1:
			dynamic_cast<Ball *>(node->getUserObject())->hit();
			break;
		case 2:
			points = dynamic_cast<Brick *>(node->getUserObject())->hit();
			if (points > 0) {
				this->addScore(points);
				checkBricks();
			}
			break;
		default:
			break;
	}
}

void GameScene::addScore(uint8_t points) {
	this->_score += points;
	this->_scoreLabel->setString(StringUtils::format("%04d", this->_score));
}

void GameScene::menuStartCallback(Ref *pSender) {
	if (this->_finished)
		this->reset();
	else
		this->startGame();
}

void GameScene::menuCloseCallback(Ref *pSender) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

void GameScene::reset() {
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void GameScene::startGame() {
	this->_controls->setEnabled(true);
	this->ball->start();
	this->_startItem->setVisible(false);
}

void GameScene::stopGame() {
	this->_finished = true;
	this->_controls->setEnabled(false);
	this->_startItem->setString("TRY AGAIN");
	this->_startItem->setVisible(true);
}

bool GameScene::checkBricks() {
	for (int l = 0; l < 3; ++l) {
		for (int c = 0; c < 4; ++c) {
			if (this->_bricks[l][c] != nullptr && this->_bricks[l][c]->remainingHits() == 0)
				return false;
		}
	}
	return true;
}