#pragma once

#include <Geode/Geode.hpp>
#include "ObjectList.hpp"

using namespace geode::prelude;

class ObjectPopup : public geode::Popup<> {

protected:
    bool setup() override;
    bool init(LevelEditorLayer* levelEditorLayer, float width, float height);
private:

    CCMenuItemToggler* m_solidsToggle;
    CCMenuItemToggler* m_hazardsToggle;
    CCMenuItemToggler* m_decorationToggle;
    CCMenuItemToggler* m_portalsToggle;
    CCMenuItemToggler* m_padsOrbsToggle;
    CCMenuItemToggler* m_triggersToggle;

    SortOptions m_sortOptions;
    LevelEditorLayer* m_editorLayer;

    void generateList(SortOptions sortOptions);
    void onSort(CCObject* sender);
    
    void onSolids(CCObject* sender);
    void onHazards(CCObject* sender);
    void onPortals(CCObject* sender);
    void onPadsOrbs(CCObject* sender);
    void onTriggers(CCObject* sender);
    void onDecoration(CCObject* sender);
    void onShowHidden(CCObject* sender);
    void disableAll();
    CCMenuItemToggler* createToggler(std::string spr, cocos2d::SEL_MenuHandler selector, bool alt, float scale);
public:
    static ObjectPopup* create(LevelEditorLayer* levelEditorLayer);
    void onClose(cocos2d::CCObject*) override;
};