//
// Created by Sylvain Kamdem on 01/04/2021.
// from Jason Xu's MyBodyParser.h
//

#include "PhysicsBodyParser.h"

USING_NS_CC;

PhysicsBodyParser *PhysicsBodyParser::instance = nullptr;

PhysicsBodyParser::PhysicsBodyParser() = default;

PhysicsBodyParser *PhysicsBodyParser::getInstance() {
	if (PhysicsBodyParser::instance == nullptr)
		PhysicsBodyParser::instance = new PhysicsBodyParser();

	return PhysicsBodyParser::instance;
}

bool PhysicsBodyParser::parse(unsigned char *buffer, long length) {
	bool result = false;
//	std::string js((const char *) buffer, length);
//	doc.Parse<0>(js.c_str());
	doc.Parse<0>(reinterpret_cast<const char *>(buffer), length);
	if (!doc.HasParseError())
		result = true;

	return result;
}

void PhysicsBodyParser::clearCache() {
	doc.SetNull();
}

bool PhysicsBodyParser::parseJsonFile(const std::string &pFile) {
	auto content = FileUtils::getInstance()->getDataFromFile(pFile);
	bool result = parse(content.getBytes(), content.getSize());
	return result;
}

//从json文件加载正确的body
PhysicsBody *PhysicsBodyParser::bodyFromJson(cocos2d::Node *pNode, const std::string &name,
											 PhysicsMaterial material) {
	PhysicsBody *body = nullptr;
	rapidjson::Value &bodies = doc["rigidBodies"];
	if (bodies.IsArray()) {
		//遍历文件中的所有body
		for (int b = 0; b < bodies.Size(); ++b) {
			//找到了请求的那一个
			if (0 == strcmp(name.c_str(), bodies[b]["name"].GetString())) {
				rapidjson::Value &bd = bodies[b];
				if (bd.IsObject()) {
					//创建一个PhysicsBody, 并且根据node的大小来设置
					body = PhysicsBody::create();
					float width = pNode->getContentSize().width;
					float offX = -pNode->getAnchorPoint().x * pNode->getContentSize().width;
					float offY = -pNode->getAnchorPoint().y * pNode->getContentSize().height;

					Point origin(bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
					rapidjson::Value &polygons = bd["polygons"];
					for (int p = 0; p < polygons.Size(); ++p) {
						int pCount = polygons[p].Size();
						Point *points = new Point[pCount];
						for (int pi = 0; pi < pCount; ++pi) {
							points[pi].x =
									offX + width * polygons[p][pCount - 1 - pi]["x"].GetDouble();
							points[pi].y =
									offY + width * polygons[p][pCount - 1 - pi]["y"].GetDouble();
						}
						body->addShape(PhysicsShapePolygon::create(points, pCount, material));
						delete[] points;
					}
				} else {
					CCLOG("body: %s not found!", name.c_str());
				}
				break;
			}
		}
	}
	return body;
}