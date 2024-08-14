#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ObjectPopup : public geode::Popup<> {

protected:
    bool setup() override;
    bool init(std::map<int, int> objectCounts, float width, float height);
    std::map<int, int> m_objectCounts;
public:
    static ObjectPopup* create(std::map<int, int> objectCounts);
    void onClose(cocos2d::CCObject*) override;
};