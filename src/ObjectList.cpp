#include "ObjectList.hpp"
#include "ObjectItem.hpp"

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
    
    std::set<int> portalObjects = { 10, 11, 12, 13, 45, 46, 47, 99, 101, 111, 200, 201, 202, 203, 286, 287, 660, 745, 747, 749, 1331, 1334, 1933, 2064, 2902, 2926 };
    std::set<int> padOrbObjects = { 35, 36, 67, 84, 140, 141, 1022, 1330, 1332, 1333, 1594, 1704, 1751, 3004, 3005, 3027 };
    std::set<int> triggerObjects = { 22, 23, 24, 25, 26, 27, 28, 32, 33, 55, 56, 57, 58, 59, 899, 901, 1006, 1007, 1049, 1268, 
                                        1346, 1347, 1520, 1585, 1595, 1611, 1612, 1613, 1616, 1811, 1812, 1814, 1815, 1817, 1818, 1819, 1912, 1913, 1914, 1915, 
                                        1916, 1917, 1932, 1934, 1935, 2015, 2016, 2062, 2066, 2067, 2068, 2899, 2900, 2901, 2903, 2904, 2905, 2907, 2909, 2910, 
                                        2911, 2912, 2913, 2914, 2915, 2916, 2917, 2919, 2920, 2921, 2922, 2923, 2924, 2925, 2999, 3006, 3007, 3008, 3009, 3010, 
                                        3011, 3012, 3013, 3014, 3015, 3016, 3017, 3018, 3019, 3020, 3021, 3022, 3023, 3024, 3029, 3030, 3031, 3032, 3033, 3600, 
                                        3602, 3603, 3604, 3605, 3606, 3607, 3608, 3609, 3612, 3613, 3614, 3615, 3617, 3618, 3619, 3620, 3641, 3642, 3660, 3661, 3662 };

    std::set<int> solidObjects = { 1, 2, 3, 4, 6, 7, 40, 62, 63, 64, 65, 66, 68, 69, 70, 71, 72, 74, 75, 76, 
                                      77, 78, 81, 82, 83, 90, 91, 92, 93, 94, 95, 96, 116, 117, 118, 119, 121, 122, 143, 146, 
                                      147, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 192, 194, 
                                      195, 196, 197, 204, 206, 207, 208, 209, 210, 212, 213, 215, 219, 220, 247, 248, 249, 250, 251, 252, 
                                      253, 254, 255, 256, 257, 258, 260, 261, 263, 264, 265, 267, 268, 269, 270, 271, 272, 274, 275, 289, 
                                      291, 294, 295, 305, 307, 321, 323, 326, 327, 331, 333, 337, 339, 343, 345, 349, 351, 353, 355, 369, 370, 371, 
                                      372, 467, 468, 469, 470, 471, 475, 483, 484, 492, 493, 651, 652, 661, 662, 663, 664, 665, 666, 673, 
                                      674, 711, 712, 726, 727, 728, 729, 886, 887, 1154, 1155, 1156, 1157, 1202, 1203, 1204, 1208, 1209, 1210, 1220, 
                                      1221, 1222, 1226, 1227, 1260, 1262, 1264, 1338, 1339, 1340, 1341, 1342, 1343, 1344, 1345, 1743, 1744, 1745, 1746, 1747, 
                                      1748, 1749, 1750, 1903, 1904, 1905, 1906, 1907, 1910, 1911 };

    std::set<int> hazardObjects = { 8, 9, 39, 61, 88, 89, 98, 103, 135, 144, 145, 177, 178, 179, 183, 184, 185, 186, 187, 188, 
                                       205, 216, 217, 218, 243, 244, 363, 364, 365, 392, 397, 398, 399, 421, 422, 446, 447, 458, 459, 667, 
                                       678, 679, 680, 720, 740, 741, 742, 768, 918, 919, 989, 991, 1327, 1328, 1582, 1584, 1619, 1620, 1701, 1702, 
                                       1703, 1705, 1706, 1707, 1708, 1709, 1710, 1711, 1712, 1713, 1714, 1715, 1716, 1717, 1718, 1719, 1720, 1721, 
                                       1722, 1723, 1724, 1725, 1726, 1727, 1728, 1729, 1730, 1731, 1732, 1733, 1734, 1735, 1736, 2012, 3034, 3035, 
                                       3036, 3037, 3610, 3611 };                 

    //std::string objectsStr = "";
    // when new objects are added, this will have to be redone

    for (auto const & [k, v] : pairs){

        //objectsStr += fmt::format("{}, ", k);
        if(k == 749) continue; //orange part of teleport

        if(sortOptions.isPortals && !(std::binary_search(portalObjects.begin(), portalObjects.end(), k))) continue;
        if(sortOptions.isPadsOrbs && !(std::binary_search(padOrbObjects.begin(), padOrbObjects.end(), k))) continue;
        if(sortOptions.isTriggers && !(std::binary_search(triggerObjects.begin(), triggerObjects.end(), k))) continue;
        if(sortOptions.isSolids && !(std::binary_search(solidObjects.begin(), solidObjects.end(), k))) continue;
        if(sortOptions.isHazards && !(std::binary_search(hazardObjects.begin(), hazardObjects.end(), k))) continue;

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