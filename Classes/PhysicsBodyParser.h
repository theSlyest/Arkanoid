//
// Created by Sylvain Kamdem on 01/04/2021.
// from Jason Xu's MyBodyParser.cpp
//

#ifndef _PHYSICS_BODY_PARSER_H_
#define _PHYSICS_BODY_PARSER_H_

#include "cocos2d.h"
#include "json/document.h"

class PhysicsBodyParser {
private:
	static PhysicsBodyParser* instance;
	rapidjson::Document doc;

	PhysicsBodyParser();

public:
	static PhysicsBodyParser* getInstance();

	bool parseJsonFile(const std::string& pFile);

	bool parse(unsigned char* buffer, long length);

	void clearCache();

	cocos2d::PhysicsBody* bodyFromJson(cocos2d::Node* pNode, const std::string& name, cocos2d::PhysicsMaterial material);
};


#endif //_PHYSICS_BODY_PARSER_H_
