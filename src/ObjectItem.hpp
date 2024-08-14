#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ObjectItem : public CCNode {
protected:
public:
    static ObjectItem* create(GameObject* go0, GameObject* go1, int count0, int count1, CCSize const& size);
private:
    bool init(GameObject* go0, GameObject* go1, int count0, int count1, CCSize const& size);
    CCNode* createNode(GameObject* object, int count);
};

