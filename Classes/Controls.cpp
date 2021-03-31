//
// Created by Sylvain Kamdem on 30/03/2021.
//

#include "Controls.h"

USING_NS_CC;

Controls::Controls(cocos2d::Scene *scene)
		: _scene(scene) {
	// Keyboard
	this->_keyboardListener = EventListenerKeyboard::create();
	this->_keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *event) {
		switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			case EventKeyboard::KeyCode::KEY_KP_LEFT:
				if (this->_onKeyPressedCallback != nullptr)
					this->_onKeyPressedCallback(false);
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			case EventKeyboard::KeyCode::KEY_KP_RIGHT:
				if (this->_onKeyPressedCallback != nullptr)
					this->_onKeyPressedCallback(true);
				break;
			default:
				break;
		}
	};
	this->_keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT ||
			keyCode == EventKeyboard::KeyCode::KEY_KP_LEFT ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT ||
			keyCode == EventKeyboard::KeyCode::KEY_KP_RIGHT) {
			if (this->_onReleaseCallback)
				this->_onReleaseCallback();
		}
	};
	this->_scene->getEventDispatcher()
			->addEventListenerWithSceneGraphPriority(this->_keyboardListener, this->_scene);
	this->_keyboardListener->setEnabled(false);

	// Touchscreen
	this->_touchscreenListener = EventListenerTouchOneByOne::create();

	this->_touchscreenListener->onTouchBegan = [this](Touch *touch, Event *event) {
		if (this->_onTouchCallback != nullptr)
			this->_onTouchCallback(touch->getLocation());
		return true;
	};

	this->_touchscreenListener->onTouchMoved = [this](Touch *touch, Event *event) {
		if (this->_onTouchCallback != nullptr)
			this->_onTouchCallback(touch->getLocation());
		return true;
	};

	this->_touchscreenListener->onTouchEnded = [this](Touch *touch, Event *event) {
		if (this->_onReleaseCallback != nullptr)
			this->_onReleaseCallback();
	};
	this->_scene->getEventDispatcher()
			->addEventListenerWithSceneGraphPriority(this->_touchscreenListener, this->_scene);
	this->_touchscreenListener->setEnabled(false);
}

void Controls::setEnabled(bool enabled) {
	this->_keyboardListener->setEnabled(enabled);
	this->_touchscreenListener->setEnabled(enabled);
}

void Controls::stopListening() {}

void Controls::onKeyPressed(const std::function<void(bool)> &cb) {
	this->_onKeyPressedCallback = cb;
}

void Controls::onRelease(const std::function<void()> &cb) {
	this->_onReleaseCallback = cb;
}

void Controls::onTouch(const std::function<void (const cocos2d::Vec2 &)> &cb) {
	this->_onTouchCallback = cb;
}

