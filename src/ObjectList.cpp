#include "ObjectList.hpp"
#include "ObjectItem.hpp"
#include "ObjectArrays.hpp"

std::string toLower(std::string str){
    std::string newStr = str;
    for(auto& c : newStr) {
        c = tolower(c);
    }
    return newStr;
}

bool ObjectList::init(std::map<int, int> objects, SortOptions sortOptions, CCSize const& size){

    this->setContentSize(size);
    this->setAnchorPoint({ 0.5f, 0.5f });

    CCScale9Sprite* bg = CCScale9Sprite::create("square02b_001.png");
    bg->setColor({ 0, 0, 0 });
    bg->setOpacity(75);
    bg->setScale(.3f);
    bg->setContentSize(size / bg->getScale());
    m_bg = bg;
    this->addChildAtPosition(
        m_bg,
        Anchor::Center
    );

    m_list = ScrollLayer::create({ size.width - 10.f, size.height - 10.f });
    m_list->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(size.height)
            ->setGap(5.0f)
    );
    this->addChildAtPosition(
        m_list,
        Anchor::Center,
        -m_list->getScaledContentSize() / 2
    );

    CCSize itemSize = {
        m_list->getScaledContentWidth(),
        24.f
    };

    std::vector<std::pair<int, int>> pairs;
    for (auto itr = objects.begin(); itr != objects.end(); ++itr){
        pairs.push_back(*itr);
    }

    sort(pairs.begin(), pairs.end(), [=](std::pair<int, int>& a, std::pair<int, int>& b){
        if (sortOptions.isAscending) return a.second < b.second;
        else return a.second > b.second;
    });

    int lastObjectID = 0;
    int lastObjectCount = 0;
    int iter = 0;

    //std::string objectsStr = "";
    // when new objects are added, this will have to be redone

    for (auto const & [k, v] : pairs){

        //objectsStr += fmt::format("{}, ", k);
        if(k < 1) continue; //skip object IDs less than 1
        if(k == 749) continue; //orange part of teleport

        if(sortOptions.isPortals && !std::ranges::binary_search(portalObjects.begin(), portalObjects.end(), k)) continue;
        if(sortOptions.isPadsOrbs && !std::ranges::binary_search(padOrbObjects.begin(), padOrbObjects.end(), k)) continue;
        if(sortOptions.isTriggers && !std::ranges::binary_search(triggerObjects.begin(), triggerObjects.end(), k)) continue;
        if(sortOptions.isSolids && !std::ranges::binary_search(solidObjects.begin(), solidObjects.end(), k)) continue;
        if(sortOptions.isHazards && !std::ranges::binary_search(hazardObjects.begin(), hazardObjects.end(), k)) continue;

        if((iter + 1) % 2 == 0){
            GameObject* gm0 = GameObject::createWithKey(lastObjectID);
            GameObject* gm1 = GameObject::createWithKey(k);
            m_list->m_contentLayer->addChild(ObjectItem::create(gm0, gm1, lastObjectCount, v, lastObjectID, k, itemSize));
        }
        else if(iter == objects.size() - 1) {
            GameObject* gm0 = GameObject::createWithKey(k);
            m_list->m_contentLayer->addChild(ObjectItem::create(gm0, nullptr, v, 0, k, 0, itemSize));
        }
        lastObjectID = k;
        lastObjectCount = v;

        iter++;
    }

    //log::info("{}", objectsStr);

    m_list->m_contentLayer->updateLayout();
    m_list->scrollToTop();

    return true;
}

ObjectList* ObjectList::create(std::map<int, int> objects, SortOptions sortOptions, CCSize const& size) {
    auto ret = new ObjectList();
    if (!ret || !ret->init(objects, sortOptions, size)) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    ret->autorelease();
    return ret;
}