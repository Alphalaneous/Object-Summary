#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct SortOptions {
    bool isAscending = false;
    bool isTriggers = false;
    bool isPortals = false;
    bool isPadsOrbs = false;
    bool isSolids = false;
    bool isHazards = false;

};

class ObjectList : public CCNode {

    protected:

        ScrollLayer* m_list;
        CCScale9Sprite* m_bg;

        bool init(std::map<int, int> objects, SortOptions sortOptions, CCSize const& size);
    public:
        static ObjectList* create(std::map<int, int> objects, SortOptions sortOptions, CCSize const& size);
};