#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "CCNodeLoaderLibrary.h"

using namespace cocos2d;
using namespace CocosDenshion;

static const int MAP_ROWS = 4;
static const int MAP_COLS = 4;

static const CCSize CELL_MARGIN(5.0f, 5.0f);

static const CCSize BACKGROUND_SIZE(600, 600);

static const CCSize CELL_AREA_SIZE(BACKGROUND_SIZE.width/MAP_COLS, BACKGROUND_SIZE.height/MAP_ROWS);

static const CCSize CELL_SIZE (CELL_AREA_SIZE.width-CELL_MARGIN.width*2, CELL_AREA_SIZE.height - CELL_MARGIN.height*2);

static ccColor3B BACKGROUND_COLOR = {166, 166 ,166};
static ccColor3B CELL_BACKGROUND_COLOR = {202, 202, 202};


int HelloWorld::createId(int cellX, int cellY)
{
    return cellY * 100 + cellX;
}

int HelloWorld::createId(CCPoint& position)
{
    return createId((int)position.x, (int)position.y);
}


CCPoint HelloWorld::getCellPosition(int id)
{
    int cellY = id / 100;
    int cellX = id % 100;
    
    return CCPoint(cellX, cellY);
}

void HelloWorld::generateRandomCells()
{
    if (emptyCells.size() > 0) {
        int index = rand() % emptyCells.size();
        int id = emptyCells[index];
        
        CCPoint position = getCellPosition(id);
        
        int value = rand()%2 == 0 ? 2 : 4;
        
        int cellX = (int)position.x;
        int cellY = (int)position.y;
        
        addCell(cellX, cellY, value, true);
    }
}


bool HelloWorld::isOver()
{
    if (emptyCells.size() > 0) {
        return false;
    }
    
    for (int row=0; row < MAP_ROWS; row++) {
        for (int col;  col < MAP_COLS - 1; col++) {
            int id = createId(col, row);
            int nextId = createId(col+1, row);
            
            if (cellData[id] == cellData[nextId]) {
                return false;
            }
        }
    }
    
    for (int col;  col < MAP_COLS; col++) {
        for (int row=0; row < MAP_ROWS - 1; row++) {
            int id = createId(col, row);
            int nextId = createId(col, row+1);
            
            if (cellData[id] == cellData[nextId]) {
                return false;
            }
        }
    }
    
    
    
    return true;
}

CCNode* HelloWorld::addCell(CCPoint& position, int value, bool animate)
{
    return addCell((int)position.x, (int)position.y, value, animate);
}



CCNode* HelloWorld::addCell(int cellX, int cellY, int value, bool animate)
{
    int id = createId(cellX, cellY);
    
    setData(id, value);
    
    CCLayerColor* cell = CCLayerColor::create();
     
    ccColor3B color = colorMap[value];//{rand()%256, rand()%256, rand()%256};
     
    cell->setColor(color);
    cell->setAnchorPoint(CCPointZero);
    cell->setContentSize(CELL_SIZE);
    cell->setOpacity(255);
    cell->setPosition(getCellPosition(cellX, cellY));
    
    CCLabelTTF* label = CCLabelTTF::create();
    //label->setString(std::to_string(value).c_str());
    label->setHorizontalAlignment(kCCTextAlignmentCenter);
    label->setFontSize(60);
    label->setPosition(CCPoint(CELL_SIZE.width/2, (CELL_SIZE.height)/2));

    cell->addChild(label);
    
    //cellPlaceholder->addChild(cell);
    background->addChild(cell);
    cell->setTag(id);
    
    if (animate) {
        cell->setScale(0);
        cell->runAction(CCScaleTo::create(.2, 1.0f));
    }
    
    return cell;
}

CCNode* HelloWorld::getCell(int id)
{
    return background->getChildByTag(id);
}

CCNode* HelloWorld::getCell(int cellX, int cellY)
{
    return getCell(createId(cellX, cellY));
}

CCNode* HelloWorld::getCell(CCPoint& position)
{
    return getCell((int)position.x, (int)position.y);
}

void HelloWorld::removeCell(int id)
{
    removeData(id);
    
    CCAssert(background->getChildByTag(id), "invalid state");
    background->removeChildByTag(id);
}

void HelloWorld::releaseEmptyCell(int id)
{
    std::vector<int>::iterator iterator = std::find(emptyCells.begin(), emptyCells.end(), id);
    
    CCAssert(iterator == emptyCells.end(), "invalid data");
    emptyCells.push_back(id);
}

void HelloWorld::removeCell(int cellX, int cellY)
{
    removeCell(createId(cellX, cellY));
}

void HelloWorld::removeCell(CCPoint& position)
{
    removeCell((int)position.x, (int)position.y);
}


CCLayerColor* HelloWorld::getCellBackground(int cellX, int cellY)
{
    return dynamic_cast<CCLayerColor*>(background->getChildByTag(createId(cellX, cellY))) ;
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbResources/ccbDefaultImages.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbResources/ccbDefaultImages.plist");
    
    m_gameOverView = loadCcb("ccbi/GameOver.ccbi");
    m_gameOverView->retain();
    
    colorMap[2] = ccc3(224,255,255);
    colorMap[4] = ccc3(175,238,238);
    colorMap[8] = ccc3(176,224,230);
    colorMap[16] = ccc3(173,216,230);
    colorMap[32] = ccc3(135,206,235);
    colorMap[64] = ccc3(135,206,250);
    colorMap[128] = ccc3(0,191,255);
    colorMap[256] = ccc3(100,149,237);
    colorMap[512] = ccc3(30,144,255);
    colorMap[1024] = ccc3(65,105,225);
    colorMap[2048] = ccc3(0,0,205);
    colorMap[4096] = ccc3(0,0,255);
    
    setAnchorPoint(CCPointZero);
    
    CCSize designSize = CCDirector::sharedDirector()->getWinSize();
    
    float backgroundXOffset = (designSize.width - BACKGROUND_SIZE.width) / 2;
    float backgroundYOffset = 100;
    
    
    background = CCLayerColor::create();
    background->setContentSize(BACKGROUND_SIZE);
    background->setColor(BACKGROUND_COLOR);
    background->setOpacity(255);
    background->setPosition(CCPoint(backgroundXOffset, backgroundYOffset));
    background->setAnchorPoint(CCPointZero);
    
    addChild(background);
    
    
    for (int i=0; i < MAP_ROWS; i++) {
        for (int j=0; j < MAP_COLS; j++) {
            CCLayerColor* cellBackground = CCLayerColor::create();
            cellBackground->setColor(CELL_BACKGROUND_COLOR);
            cellBackground->setPosition(CCPoint(CELL_AREA_SIZE.width*j + CELL_MARGIN.width,CELL_AREA_SIZE.height*i + CELL_MARGIN.height));
            cellBackground->setAnchorPoint(CCPointZero);
            cellBackground->setContentSize(CELL_SIZE);
            cellBackground->setOpacity(255);
            
            int id = createId(j, i);
//            cellBackground->setTag(id);
            
            background->addChild(cellBackground);
            
            emptyCells.push_back(id);
        }
    }
    
    setContentSize(designSize);
    
    generateRandomCells();
    generateRandomCells();
    generateRandomCells();
    
    return true;
}

CCPoint HelloWorld::getCellPosition(int cellX, int cellY)
{
    return CCPoint(CELL_AREA_SIZE.width*cellX + CELL_MARGIN.width,CELL_AREA_SIZE.height*cellY + CELL_MARGIN.height);
}

CCPoint HelloWorld::getCellPosition(CCPoint& position)
{
    return getCellPosition((int)position.x, (int)position.y);
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iterator = pTouches->begin();
    CCTouch* touch =  dynamic_cast<CCTouch*>(*iterator);
    
    if (touch) {
        CCPoint position = touch->getLocation();
        touchStartLocation.setPoint(position.x, position.y);
        
    }
}

CCNode* HelloWorld::loadCcb(std::string fileName)
{
    /* get shared CCNodeLoaderLibrary */
	cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	/* Create an CCBReader. */
	cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
	CCNode * node = ccbReader->readNodeGraphFromFile(fileName.c_str(), this,CCDirector::sharedDirector()->getWinSize());
    ccbReader->release();
    return node;
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    
}
void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iterator = pTouches->begin();
    CCTouch* touch =  dynamic_cast<CCTouch*>(*iterator);
    
    if (touch) {
        CCPoint position = touch->getLocation();
        CCPoint delta = position - touchStartLocation;
        
        float dx = abs(delta.x);
        float dy = abs(delta.y);
        
        if (dx <= dy)
        {
            if (delta.y >= 0)
            {
                moveUp();
            }
            else
            {
                moveDown();
            }
        }
        else
        {
            if (delta.x >= 0) {
                moveRight();
            }
            else
            {
                moveLeft();
            }
        }
        
        generateRandomCells();
        
        if (isOver()) {
            CCSize designSize = CCDirector::sharedDirector()->getWinSize();
            
            m_gameOverView->setPosition(designSize.width/2, designSize.height/2);
            addChild(m_gameOverView);
        }
    }
}

void HelloWorld::getElementsInRow(ElementVector& elements, int row)
{
    for (int col =0; col < MAP_COLS; col++) {
        ElementVector elements;
        int id = createId(col, row);
        if (cellData.find(id) != cellData.end()) {
            CCPoint position = getCellPosition(id);
            int value = cellData[id];
            
            Element e(position, value);
            
            elements.push_back(e);
            
        }
    }
}
void HelloWorld::getElementsInColumn(ElementVector& elements, int col)
{
    for (int row=0; row < MAP_ROWS; row++) {
        int id = createId(col, row);
        if (cellData.find(id) != cellData.end()) {
            CCPoint position = getCellPosition(id);
            int value = cellData[id];
            
            Element e(position, value);
            
            elements.push_back(e);
            
        }
    }
}

void HelloWorld::moveUp()
{
    
    for (int col =0; col < MAP_COLS; col++) {
        ElementVector elements;
        getElementsInColumn(elements, col);
        
        std::vector<ProcessedElement> processedElements;
        
        for (int i=0; i < elements.size(); i++) {
            Element* currentElement = &elements[i];
            
            if (i+1 >= elements.size()) {
                ProcessedElement pe;
                pe.setResult(ProcessResultKeep);
                pe.setE1(currentElement);
                
                processedElements.insert(processedElements.begin(), pe);
            }
            else
            {
                Element* nextElement = &elements[i+1];
                
                if (currentElement->value == nextElement->value) {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultMerge);
                    pe.setE1(currentElement);
                    pe.setE2(nextElement);
                    
                    processedElements.insert(processedElements.begin(), pe);
                    
                    i++;
                }
                else
                {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultKeep);
                    pe.setE1(currentElement);
                    
                    processedElements.insert(processedElements.begin(), pe);
                    
                }
            }
        }
        
        for (int i=0, newIndex=MAP_ROWS-1; i <processedElements.size(); i++,newIndex--) {
            ProcessedElement* element = &processedElements[i];
            element->newPosition.setPoint(col, newIndex);
        }
        
        for (int i=0; i < processedElements.size(); i++) {
            ProcessedElement* element = &processedElements[i];
            
            switch (element->getResult()) {
                case ProcessResultMerge:
                {
                    removeCell(element->getE1()->position);
                    removeCell(element->getE2()->position);
                    
                    int newValue = element->getE1()->value + element->getE2()->value;
                    
                    CCNode* newCell = addCell(element->newPosition, newValue);
                    newCell->setPosition(getCellPosition(element->getE1()->position));
                    newCell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    
                }
                    break;
                case ProcessResultKeep:
                {
                    int id = createId(element->getE1()->position);
                    CCNode* cell = getCell(id);
                    
                    int id1 = createId(element->getE1()->position);
                    int id2 = createId(element->newPosition);
                    if (id1 != id2) {
                        
                        removeData(id1);
                        setData(id2, element->getE1()->value);
                        
                        cell->setTag(createId(element->newPosition));
                        cell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    }
                }
                    break;
                default:
                    CCAssert(false, "Unknown process result");
                    break;
            }
        }
        
        
    }
    
    
}

void HelloWorld::moveDown()
{
    for (int col =0; col < MAP_COLS; col++) {
        ElementVector elements;
        getElementsInColumn(elements, col);
        
        std::vector<ProcessedElement> processedElements;
        
        for (int i=elements.size()-1; i >= 0; i--) {
            Element* currentElement = &elements[i];
            
            if (i-1 < 0) {
                ProcessedElement pe;
                pe.setResult(ProcessResultKeep);
                pe.setE1(currentElement);
                
                processedElements.insert(processedElements.begin(), pe);
            }
            else
            {
                Element* nextElement = &elements[i-1];
                
                if (currentElement->value == nextElement->value) {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultMerge);
                    pe.setE1(currentElement);
                    pe.setE2(nextElement);
                    
                    processedElements.insert(processedElements.begin(), pe);
                    
                    i--;
                }
                else
                {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultKeep);
                    pe.setE1(currentElement);
                    
                    processedElements.insert(processedElements.begin(), pe);
                    
                }
            }
        }
        
        for (int i=0; i <processedElements.size(); i++) {
            ProcessedElement* element = &processedElements[i];
            element->newPosition.setPoint(col, i);
        }
        
        for (int i=0; i < processedElements.size(); i++) {
            ProcessedElement* element = &processedElements[i];
            
            switch (element->getResult()) {
                case ProcessResultMerge:
                {
                    removeCell(element->getE1()->position);
                    removeCell(element->getE2()->position);
                    
                    int newValue = element->getE1()->value + element->getE2()->value;
                    
                    CCNode* newCell = addCell(element->newPosition, newValue);
                    newCell->setPosition(getCellPosition(element->getE1()->position));
                    newCell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    
                }
                    break;
                case ProcessResultKeep:
                {
                    int id = createId(element->getE1()->position);
                    CCNode* cell = getCell(id);
                    
                    int id1 = createId(element->getE1()->position);
                    int id2 = createId(element->newPosition);
                    if (id1 != id2) {
                        
                        removeData(id1);
                        setData(id2, element->getE1()->value);
                        
                        cell->setTag(createId(element->newPosition));
                        cell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    }
                }
                    break;
                default:
                    CCAssert(false, "Unknown process result");
                    break;
            }
        }
        
        
    }
}

void HelloWorld::moveLeft()
{
    for (int row=0; row < MAP_ROWS; row++) {
        std::vector<Element> elements;
        
        for (int col=0; col < MAP_COLS; col++) {
            
            int id = createId(col, row);
            if (cellData.find(id) != cellData.end()) {
                CCPoint position = getCellPosition(id);
                int value = cellData[id];
                
                Element e(position, value);
                
                elements.push_back(e);
                
            }
            
        }
        
        std::vector<ProcessedElement> processedElements;
        
        for (int i=elements.size()-1; i>= 0; i--) {
            Element* currentElement = &elements[i];
            
            if (i-1 < 0) {
                ProcessedElement pe;
                pe.setResult(ProcessResultKeep);
                pe.setE1(currentElement);
                
                processedElements.insert(processedElements.begin(), pe);
            }
            else
            {
                Element* nextElement = &elements[i-1];
                
                if (currentElement->value == nextElement->value) {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultMerge);
                    pe.setE1(currentElement);
                    pe.setE2(nextElement);
                    
                    processedElements.insert(processedElements.begin(), pe);
                    
                    i--;
                }
                else
                {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultKeep);
                    pe.setE1(currentElement);
                    
                    processedElements.insert(processedElements.begin(), pe);
                    
                }
            }
        }
        
        
        for (int i=0; i <processedElements.size(); i++) {
            ProcessedElement* element = &processedElements[i];
            element->newPosition.setPoint(i, row);
        }
        
        for (int i=0; i < processedElements.size(); i++) {
            ProcessedElement* element = &processedElements[i];
            
            switch (element->getResult()) {
                case ProcessResultMerge:
                {
                    removeCell(element->getE1()->position);
                    removeCell(element->getE2()->position);
                    
                    int newValue = element->getE1()->value + element->getE2()->value;
                    
                    CCNode* newCell = addCell(element->newPosition, newValue);
                    newCell->setPosition(getCellPosition(element->getE1()->position));
                    newCell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    
                }
                    break;
                case ProcessResultKeep:
                {
                    int id = createId(element->getE1()->position);
                    CCNode* cell = getCell(id);
                    
                    int id1 = createId(element->getE1()->position);
                    int id2 = createId(element->newPosition);
                    if (id1 != id2) {
                        
                        removeData(id1);
                        setData(id2, element->getE1()->value);
                        
                        cell->setTag(createId(element->newPosition));
                        cell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    }
                }
                    break;
                default:
                    CCAssert(false, "Unknown process result");
                    break;
            }
        }
    }
}

void HelloWorld::removeData(int id)
{
    CCAssert(cellData.find(id) != cellData.end(), "data not exist");
    cellData.erase(cellData.find(id));
    
    releaseEmptyCell(id);
}

void HelloWorld::setData(CCPoint& position, int value)
{
    setData((int)position.x, (int)position.y, value);
}

void HelloWorld::setData(int id, int value)
{
    cellData[id] = value;
 
    //maybe it's not taken
    std::vector<int>::iterator iterator = std::find(emptyCells.begin(), emptyCells.end(), id);
    if (iterator != emptyCells.end()) {
        emptyCells.erase(iterator);
    }

}

void HelloWorld::setData(int cellX, int cellY, int value)
{
    int id = createId(cellX, cellY);
    setData(id, value);
}

void HelloWorld::moveRight()
{
    for (int row=0; row < MAP_ROWS; row++) {
        std::vector<Element> elements;
        
        for (int col=0; col < MAP_COLS; col++) {

            int id = createId(col, row);
            if (cellData.find(id) != cellData.end()) {
                CCPoint position = getCellPosition(id);
                int value = cellData[id];
                
                Element e(position, value);
                
                elements.push_back(e);
                
            }
            
        }
        
        std::vector<ProcessedElement> processedElements;
        
        for (int i=0; i<elements.size(); i++) {
            Element* currentElement = &elements[i];
            
            if (i+1 >= elements.size()) {
                ProcessedElement pe;
                pe.setResult(ProcessResultKeep);
                pe.setE1(currentElement);
                
                processedElements.push_back(pe);
            }
            else
            {
                Element* nextElement = &elements[i+1];
                
                if (currentElement->value == nextElement->value) {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultMerge);
                    pe.setE1(currentElement);
                    pe.setE2(nextElement);
                    
                    processedElements.push_back(pe);
                    
                    i++;
                }
                else
                {
                    ProcessedElement pe;
                    pe.setResult(ProcessResultKeep);
                    pe.setE1(currentElement);
                    
                    processedElements.push_back(pe);
                }
            }
        }
        
        for (int i=processedElements.size()-1, newIndex=MAP_COLS-1; i >= 0; i--,newIndex--) {
            ProcessedElement* element = &processedElements[i];
            element->newPosition.setPoint(newIndex, row);
        }
        
        for (int i=processedElements.size()-1; i >= 0; i--) {
            ProcessedElement* element = &processedElements[i];

            switch (element->getResult()) {
                case ProcessResultMerge:
                {
                    removeCell(element->getE1()->position);
                    removeCell(element->getE2()->position);
                    
                    int newValue = element->getE1()->value + element->getE2()->value;
                    
                    CCNode* newCell = addCell(element->newPosition, newValue);
                    newCell->setPosition(getCellPosition(element->getE1()->position));
                    newCell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    
                }
                    break;
                case ProcessResultKeep:
                {
                    int id = createId(element->getE1()->position);
                    
                    
                    int id1 = createId(element->getE1()->position);
                    int id2 = createId(element->newPosition);
                    if (id1 != id2) {
                        removeData(id1);
                        
                        setData(id2, element->getE1()->value);
                        
                        CCNode* cell = getCell(id);
                        
                        cell->setTag(createId(element->newPosition));
                        cell->runAction(CCMoveTo::create(.2, getCellPosition(element->newPosition)));
                    }
                }
                    break;
                default:
                    CCAssert(false, "Unknown process result");
                    break;
            }
        }
    }
    
    
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
