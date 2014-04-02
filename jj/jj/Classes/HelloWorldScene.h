#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <map>

USING_NS_CC;

typedef enum
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
} MoveDirection;

class Element
{
public:
    Element(CCPoint& position, int value)
    {
        this->position.setPoint(position.x, position.y);
        this->value = value;
    }
    
    CCPoint position;
    CCPoint to;
    
    int value;
};

typedef enum
{
    ProcessResultMerge,
    ProcessResultKeep
} ProcessedElementResult;

class ProcessedElement
{
public:
    ProcessedElement():m_e1(NULL),m_e2(NULL)
    {
        
    }
    
    CCPoint newPosition;
    
    CC_SYNTHESIZE(ProcessedElementResult, m_result, Result);
    CC_SYNTHESIZE(int, m_oldValue, OldValue);
    CC_SYNTHESIZE(int, m_newValue, NewValue);
    
    CC_SYNTHESIZE(Element*, m_e1, E1);
    CC_SYNTHESIZE(Element*, m_e2, E2);
    
};

typedef std::vector<Element> ElementVector;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    CCPoint getCellPosition(int cellX, int cellY);
    CCPoint getCellPosition(CCPoint& position);
    
    int createId(int cellX, int cellY);
    int createId(CCPoint& position);
    
    
    void getElementsInRow(ElementVector& elements, int row);
    void getElementsInColumn(ElementVector& elements, int col);
    
    CCPoint getCellPosition(int id);
    
    CCLayerColor* getCellBackground(int cellX, int cellY);
    
    CCNode* addCell(int cellX, int cellY, int value, bool animate=false);
    CCNode* addCell(CCPoint& position, int value, bool animate=false);
    
    CCNode* getCell(int id);
    CCNode* getCell(int cellX, int cellY);
    CCNode* getCell(CCPoint& position);
    
    void removeData(int id);
    
    void setData(CCPoint& position, int value);
    void setData(int cellX, int cellY, int value);
    void setData(int id, int value);
    
    void removeCell(int cellX, int cellY);
    void removeCell(CCPoint& position);
    void removeCell(int id);
    
    void releaseEmptyCell(int id);
    
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    
    bool isEmpty(int cellX, int cellY);
    
    bool isOver();
    
    void generateRandomCells();
    
    CCPoint touchStartLocation;
    CCLayerColor* background;
    std::map<int,int> cellData;
    std::vector<int> emptyCells;
    
    CCNode* loadCcb(std::string fileName);
    
    CCNode* m_gameOverView;
    
    std::map<int,ccColor3B> colorMap;
};

#endif // __HELLOWORLD_SCENE_H__
