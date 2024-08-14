#include "ObjectList.hpp"
#include "ObjectItem.hpp"

std::string toLower(std::string str){
    std::string newStr = str;
    for(auto& c : newStr) {
        c = tolower(c);
    }
    return newStr;
}

bool ObjectList::init(std::map<int, int> objects, CCSize const& size){

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
        return a.second > b.second;
    });

    int lastObjectID = 0;
    int lastObjectCount = 0;
    int iter = 0;
    
    for (auto const & [k, v] : pairs){
        if((iter + 1) % 2 == 0){
            GameObject* gm0 = GameObject::createWithKey(lastObjectID);
            GameObject* gm1 = GameObject::createWithKey(k);
            m_list->m_contentLayer->addChild(ObjectItem::create(gm0, gm1, lastObjectCount, v, itemSize));
        }
        else if(iter == objects.size() - 1) {
            GameObject* gm0 = GameObject::createWithKey(k);
            m_list->m_contentLayer->addChild(ObjectItem::create(gm0, nullptr, v, 0, itemSize));
        }
        lastObjectID = k;
        lastObjectCount = v;

        iter++;
    }

    m_list->m_contentLayer->updateLayout();
    m_list->scrollToTop();

    return true;
}

ObjectList* ObjectList::create(std::map<int, int> objects, CCSize const& size) {
    auto ret = new ObjectList();
    if (!ret || !ret->init(objects, size)) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    ret->autorelease();
    return ret;
}