#include "ObjectItem.hpp"
#include <Geode/utils/ColorProvider.hpp>
#include <Geode/ui/GeodeUI.hpp>

bool ObjectItem::init(GameObject* go0, GameObject* go1, int count0, int count1, CCSize const& size) {
    if (!CCNode::init()) {
        return false;
    }

    this->setContentSize(size);
    this->setAnchorPoint({ 0.5f, 0.5f });

    RowLayout* layout = RowLayout::create();
    layout->setAutoScale(false);
    layout->setGap(0);
    setLayout(layout);

    addChild(createNode(go0, count0));
    if(go1) addChild(createNode(go1, count1));

    updateLayout();

    return true;
}

CCNode* ObjectItem::createNode(GameObject* object, int count){

    CCSize contentSize = getContentSize();
    float realWidth = contentSize.width/2;

    CCNode* objectNode = CCNode::create();
    CCLabelBMFont* countLabel = CCLabelBMFont::create(fmt::format("{}x", count).c_str(), "bigFont.fnt");
    countLabel->setAnchorPoint({1, 0.5});
    countLabel->setScale(0.5f);

    CCNode* objectContainer = CCNode::create();
    objectContainer->setContentSize({contentSize.height, contentSize.height});
    objectContainer->setPosition({realWidth, contentSize.height/2});
    objectContainer->setAnchorPoint({1, 0.5});

    float scale = 1;

    if(object->getContentSize().height > contentSize.height && object->getContentSize().height > object->getContentSize().width){
        scale = contentSize.height/object->getContentSize().height;
    }
    else if (object->getContentSize().width > contentSize.height){
        scale = contentSize.height/object->getContentSize().width;
    }

    std::string frame = ObjectToolbox::sharedState()->intKeyToFrame(object->m_objectID);

    if(frame == "emptyFrame.png"){
        scale = 0.75;
    }

    if(object->m_objectID == 914){
        CCLabelBMFont* textLabel = CCLabelBMFont::create("A", "bigFont.fnt");
        textLabel->setPosition({contentSize.height/2, contentSize.height/2});
        textLabel->setScale(0.75f);
        objectContainer->addChild(textLabel);
    }

    object->setScale(scale * 0.75f);
    object->addColorSprite(frame);
    object->setupCustomSprites(frame);
    objectContainer->addChild(object);

    if(object->m_objectID == 1049){
        if(CCSprite* spr = object->getChildByType<CCSprite>(0)) {
            spr->setColor({255, 63, 63});
        }
    }

    object->setPosition({contentSize.height/2, contentSize.height/2});

    countLabel->setPosition({realWidth - (24 * 0.75f) - 6, contentSize.height/2});

    objectNode->setContentSize({realWidth, contentSize.height});
    objectNode->addChild(countLabel);
    objectNode->addChild(objectContainer);

    return objectNode;
}


ObjectItem* ObjectItem::create(GameObject* go0, GameObject* go1, int count0, int count1, CCSize const& size) {
    auto ret = new ObjectItem();
    if (!ret || !ret->init(go0, go1, count0, count1, size)) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    ret->autorelease();
    return ret;
}