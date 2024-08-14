#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ObjectList : public CCNode {

    protected:

        ScrollLayer* m_list;
        CCScale9Sprite* m_bg;

        bool init(std::map<int, int> objects, CCSize const& size);
    public:
        static ObjectList* create(std::map<int, int> objects, CCSize const& size);
};