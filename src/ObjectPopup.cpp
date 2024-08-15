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

    generateList(m_sortOptions);

    CCLabelBMFont* uniqueLabel = CCLabelBMFont::create(fmt::format("{} unique objects", m_objectCounts.size()).c_str(), "bigFont.fnt");
    uniqueLabel->setScale(0.35f);
    uniqueLabel->setOpacity(127);

    m_mainLayer->addChildAtPosition(
        uniqueLabel,
        Anchor::Bottom,
        { 0.0f, 18.0f }
    );

    CCMenu* sortButtons = CCMenu::create();
    sortButtons->setContentSize({20, 280});
    ColumnLayout* layout = ColumnLayout::create();
    layout->setAxisAlignment(AxisAlignment::End);
    layout->setAxisReverse(true);
    sortButtons->setLayout(layout);

    sortButtons->addChild(createToggler("GJ_sortIcon_001.png", menu_selector(ObjectPopup::onSort), false, 1));

    CCNode* emptyDivider = CCNode::create();
    emptyDivider->setContentSize({1, 5});
    sortButtons->addChild(emptyDivider);

    m_solidsToggle = createToggler("square_01_001.png", menu_selector(ObjectPopup::onSolids), true, 0.85f);
    m_hazardsToggle = createToggler("spike_01_001.png", menu_selector(ObjectPopup::onHazards), true, 0.85f);
    m_portalsToggle = createToggler("portal_04_front_001.png", menu_selector(ObjectPopup::onPortals), true, 1);
    m_padsOrbsToggle = createToggler("ring_01_001.png", menu_selector(ObjectPopup::onPadsOrbs), true, 0.75f);
    m_triggersToggle = createToggler("edit_eSpawnBtn_001.png", menu_selector(ObjectPopup::onTriggers), true, 0.85f);

    sortButtons->addChild(m_solidsToggle);
    sortButtons->addChild(m_hazardsToggle);
    sortButtons->addChild(m_portalsToggle);
    sortButtons->addChild(m_padsOrbsToggle);
    sortButtons->addChild(m_triggersToggle);

    sortButtons->setScale(0.65f);

    sortButtons->updateLayout();

    m_mainLayer->addChildAtPosition(
        sortButtons,
        Anchor::Left,
        { -16.0f, -15.0f }
    );

    return true;
}

CCMenuItemToggler* ObjectPopup::createToggler(std::string spr, cocos2d::SEL_MenuHandler selector, bool alt, float scale){

    CCSprite* onSpr = CCSprite::createWithSpriteFrameName(spr.c_str());
    CCSprite* offSpr = CCSprite::createWithSpriteFrameName(spr.c_str());

    std::string onSprStr;
    std::string offSprStr;

    if (!alt) {
        onSprStr = "GJ_button_01.png";
        offSprStr = "GJ_button_03.png";
    }
    else {
        onSprStr = "GJ_button_05.png";
        offSprStr = "GJ_button_02.png";
    }

    ButtonSprite* on = ButtonSprite::create(onSpr, 30, true, 30, onSprStr.c_str(), scale);
    ButtonSprite* off = ButtonSprite::create(offSpr, 30, true, 30, offSprStr.c_str(), scale);

    onSpr->setPosition({on->getContentSize().width/2, on->getContentSize().height/2});
    offSpr->setPosition({off->getContentSize().width/2, off->getContentSize().height/2});

    return CCMenuItemToggler::create(on, off, this, selector);
}

void ObjectPopup::onSort(CCObject* sender){
    CCMenuItemToggler* toggler = typeinfo_cast<CCMenuItemToggler*>(sender);
    m_sortOptions.isAscending = !toggler->isOn();
    generateList(m_sortOptions);
}

void ObjectPopup::disableAll() {
    m_sortOptions.isSolids = false;
    m_sortOptions.isPortals = false;
    m_sortOptions.isPadsOrbs = false;
    m_sortOptions.isTriggers = false;
    m_sortOptions.isHazards = false;

    m_solidsToggle->toggle(false);
    m_hazardsToggle->toggle(false);
    m_portalsToggle->toggle(false);
    m_padsOrbsToggle->toggle(false);
    m_triggersToggle->toggle(false);
}

void ObjectPopup::onSolids(CCObject* sender){
    CCMenuItemToggler* toggler = typeinfo_cast<CCMenuItemToggler*>(sender);
    bool state = toggler->isOn();
    disableAll();
    toggler->toggle(state);
    m_sortOptions.isSolids = !toggler->isOn();
    generateList(m_sortOptions);
}

void ObjectPopup::onHazards(CCObject* sender){
    CCMenuItemToggler* toggler = typeinfo_cast<CCMenuItemToggler*>(sender);
    bool state = toggler->isOn();
    disableAll();
    toggler->toggle(state);
    m_sortOptions.isHazards = !toggler->isOn();
    generateList(m_sortOptions);
}

void ObjectPopup::onPortals(CCObject* sender){
    CCMenuItemToggler* toggler = typeinfo_cast<CCMenuItemToggler*>(sender);
    bool state = toggler->isOn();
    disableAll();
    toggler->toggle(state);
    m_sortOptions.isPortals = !toggler->isOn();
    generateList(m_sortOptions);
}

void ObjectPopup::onPadsOrbs(CCObject* sender){
    CCMenuItemToggler* toggler = typeinfo_cast<CCMenuItemToggler*>(sender);
    bool state = toggler->isOn();
    disableAll();
    toggler->toggle(state);
    m_sortOptions.isPadsOrbs = !toggler->isOn();
    generateList(m_sortOptions);
}

void ObjectPopup::onTriggers(CCObject* sender){
    CCMenuItemToggler* toggler = typeinfo_cast<CCMenuItemToggler*>(sender);
    bool state = toggler->isOn();
    disableAll();
    toggler->toggle(state);
    m_sortOptions.isTriggers = !toggler->isOn();
    generateList(m_sortOptions);
}

void ObjectPopup::generateList(SortOptions sortOptions){

    m_mainLayer->removeChildByID("object-list");
    ObjectList* list = ObjectList::create(m_objectCounts, sortOptions, {m_mainLayer->getContentSize().width-40, 150.f});
    list->setID("object-list");
    
    m_mainLayer->addChildAtPosition(
        list,
        Anchor::Center,
        { 0.0f, -5.0f }
    );
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