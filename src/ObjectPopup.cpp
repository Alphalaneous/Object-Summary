#include "ObjectPopup.hpp"
#include "ObjectList.hpp"

bool ObjectPopup::init(std::map<int, int> objectCounts, float width, float height){
  
    m_objectCounts = objectCounts;

    if (!Popup<>::initAnchored(width, height, "GJ_square01.png")) return false;

    this->setCloseButtonSpr(
        CircleButtonSprite::createWithSpriteFrameName(
            "geode.loader/close.png", .85f,
            CircleBaseColor::Green
        )
    );

    return true;
}

bool ObjectPopup::setup() {

    this->setTitle("Object Summary:");
    m_title->limitLabelWidth(m_mainLayer->getContentSize().width - 50, .7f, .1f);

    ObjectList* list = ObjectList::create(m_objectCounts, {m_mainLayer->getContentSize().width-40, 150.f});

    m_mainLayer->addChildAtPosition(
        list,
        Anchor::Center,
        { 0.0f, -5.0f }
    );

    CCLabelBMFont* uniqueLabel = CCLabelBMFont::create(fmt::format("{} unique objects", m_objectCounts.size()).c_str(), "bigFont.fnt");
    uniqueLabel->setScale(0.35f);
    uniqueLabel->setOpacity(127);

    m_mainLayer->addChildAtPosition(
        uniqueLabel,
        Anchor::Bottom,
        { 0.0f, 18.0f }
    );

    return true;
}

void ObjectPopup::onClose(cocos2d::CCObject*){
    this->setKeypadEnabled(false);
    this->setTouchEnabled(false);
    this->removeFromParentAndCleanup(true);
}

ObjectPopup* ObjectPopup::create(std::map<int, int> objectCounts) {

    auto ret = new ObjectPopup();
    if (ret->init(objectCounts, 240.f, 220.f)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}