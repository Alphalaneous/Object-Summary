#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSettingsLayer.hpp>
#include "ObjectPopup.hpp"

using namespace geode::prelude;

class $modify(MyLevelSettingsLayer, LevelSettingsLayer) {
	bool init(LevelSettingsObject* p0, LevelEditorLayer* p1) {
		if (!LevelSettingsLayer::init(p0, p1)) return false;

		CCMenu* newMenu = CCMenu::create();
		newMenu->setID("object-summary-menu"_spr);
		newMenu->ignoreAnchorPointForPosition(false);
		m_mainLayer->addChild(newMenu);

		CCLabelBMFont* tempLabel = CCLabelBMFont::create("S", "bigFont.fnt");

        auto spr = CircleButtonSprite::createWithSpriteFrameName(
            "square_01_001.png", 0.75f,
            CircleBaseColor::Green
        );
		spr->setScale(0.85f);

		CCMenuItemSpriteExtra* summaryButton = CCMenuItemSpriteExtra::create(spr, this, menu_selector(MyLevelSettingsLayer::showObjectSummary));

		CCSize winSize = CCDirector::get()->getWinSize();
		summaryButton->setPosition({winSize.width/2 - 185, winSize.height/2 - 115});

		newMenu->addChild(summaryButton);

		handleTouchPriority(this);

		return true;
	}

	void showObjectSummary(CCObject* sender) {

		std::map<int, int> objectCounts;

		for(GameObject* obj : CCArrayExt<GameObject*>(m_editorLayer->m_objects)){
			objectCounts[obj->m_objectID]++;
		}

		ObjectPopup::create(objectCounts)->show();
	}
};
