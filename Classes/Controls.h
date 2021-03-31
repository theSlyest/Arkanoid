//
// Created by Sylvain Kamdem on 30/03/2021.
//

#ifndef _GAME_CONTROLS_H_
#define _GAME_CONTROLS_H_

#include "cocos2d.h"

class Controls {
public:
	Controls(cocos2d::Scene* scene);

	void setEnabled(bool enabled);

	void stopListening();

	void onKeyPressed(const std::function<void(bool)> &cb);
	void onTouch(const std::function<void(const cocos2d::Vec2 &)> &cb);
	void onRelease(const std::function<void()> &cb);

private:
	cocos2d::Scene* _scene;
	cocos2d::EventListenerKeyboard* _keyboardListener;
	cocos2d::EventListenerTouchOneByOne* _touchscreenListener;

	std::function<void(bool)> _onKeyPressedCallback;
	std::function<void(const cocos2d::Vec2 &)> _onTouchCallback;
	std::function<void()> _onReleaseCallback;
};


#endif //_GAME_CONTROLS_H_
