//
//  T28Chess.h
//  
//
//  Created by 薛国良 on 15/11/22.
//
//

#ifndef ____T28Chess__
#define ____T28Chess__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

// 棋盘的左下角坐标是0， 0
// stoneid 从0到31，那么0表示什么，1表示什么....31表示什么
// 由我们自己定义的

/*
 1. 定义：
    棋盘坐标：左下角为0，0坐标
    id和棋子的对应对应关系
    
 
    0 - 1 - 2 - 3 - 4
    - - - - - - - - -
    - - - - - - - - -
    b - c - d - e - f
    - 9 - - - - - a -
    - - - - - - - - -
    0 1 2 3 4 5 6 7 8
 */

class Stone : public Sprite
{
public:
    enum Type{JIANG, SHI, XIANG, CHE, MA, PAO, BING, COUNT};
    static Stone* create(int stoneid)
    {
        Stone* s = new Stone;
        s->autorelease();
        s->init(stoneid);
        return s;
    }
    
    Type getType(int stoneid)
    {
        Type types[] = {CHE, MA, XIANG, SHI, JIANG, SHI, XIANG, MA, CHE,
        PAO, PAO,
        BING, BING, BING, BING, BING,
        BING, BING, BING, BING, BING,
        PAO, PAO,
            CHE, MA, XIANG, SHI, JIANG, SHI, XIANG, MA, CHE};
        return types[stoneid];
    }
    
    void initRowCol(int stoneid)
    {
        int rows[] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 2, 3, 3, 3, 3, 3,
        6, 6, 6,6, 6, 7, 7,
        9, 9, 9, 9, 9, 9, 9, 9, 9};
        int cols[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                    1, 7,
                    0, 2, 4, 6, 8,
                    0, 2, 4, 6, 8,
                    1, 7,
                    0, 1, 2, 3, 4, 5, 6, 7, 8};
        
        _row = rows[stoneid];
        _col = cols[stoneid];
    }
    
    // enum Type{JIANG, SHI, XIANG, CHE, MA, PAO, BING, COUNT}
    void initScore()
    {
        int score[] = {30000, 50, 50, 500, 250, 250, 100};
        _score = score[_type];
    }
    
    int getScore()
    {
        if(_dead) return 0;
        
        return _score;
    }
    
    bool init(int stoneid)
    {
        // 通过id获得type，再经过type获得文件路径
        
        _type = getType(stoneid);
        _color = stoneid < 16;
        
        const char* bStoneFile[] = {
            "bjiang.png", "bshi.png", "bxiang.png", "bche.png",
            "bma.png", "bpao.png", "bzu.png"
        };
        const char* rStoneFile[] = {
            "rshuai.png", "rshi.png", "rxiang.png", "rche.png",
            "rma.png", "rpao.png", "rbing.png"
        };
        
        const char** p = _color ?rStoneFile :bStoneFile;
        
        char stoneFileName[256];
        sprintf(stoneFileName, "chess/%s", p[_type]);
        Sprite::initWithFile(stoneFileName);
        
        _dead = false;
        _stoneId = stoneid;
        initRowCol(stoneid);
        
        // 用在人工智能
        initScore();
        
        return true;
    }
    
    
    
    bool _color;
    Type _type;
    int _row; // 棋盘的位置
    int _col;
    bool _dead;
    int _stoneId; // 0~31下标
    int _score;
};

class Move : public Ref
{
public:
    static Move* create(int moveid, int killid, int row, int col, int rowFrom, int colFrom)
    {
        Move* ret = new Move;
        ret->autorelease();
        ret->init(moveid, killid, row, col, rowFrom, colFrom);
        return ret;
    }
    
    void init(int moveid, int killid, int row, int col, int rowFrom, int colFrom)
    {
        _moveid = moveid;
        _killid = killid;
        _row = row;
        _col = col;
        _rowFrom = rowFrom;
        _colFrom = colFrom;
    }
    
    int _moveid;
    int _killid;
    int _row;
    int _col;
    int _rowFrom;
    int _colFrom;
};

class T28Chess : public Layer
{
public:
    
    CREATE_FUNC(T28Chess);
    bool init();
    
    Sprite* _selectedFlag;
    
    Stone* _stone[32];
    
    int _stoneids[10][9];
    
    
    int _d;    // 象棋格子的尺寸
    Vec2 _off; // 象棋坐标原点和窗口坐标原点的偏移
    
    bool _bRedTurn;

    int _selectid; // 被选中的棋子的id
    void selectStone(Touch* touch);
    void moveStone(Touch* touch);
    
    // 获取两个坐标之间的棋子个数
    // 如果row1 col1到row2 col2之间不是一条直线，返回－1
    //
    int getStoneCount(int row1, int col1, int row2, int col2);
    int getStoneId(int row, int col);
    
    bool canMove(int moveid, int killid, int row, int col);
    bool canMoveCHE(int moveid, int killid, int row, int col);
    bool canMoveMA(int moveid, int killid, int row, int col);
    bool canMovePAO(int moveid, int killid, int row, int col);
    bool canMoveBING(int moveid, int killid, int row, int col);
    bool canMoveJIANG(int moveid, int killid, int row, int col);
    bool canMoveSHI(int moveid, int killid, int row, int col);
    bool canMoveXIANG(int moveid, int killid, int row, int col);
    
    // 人工智能
    void ComputerMove(int level);
    void getAllPossibleMove(Vector<Move*>& moves, bool debug=false);
    void getAllPossibleMoveChe(int sid, Vector<Move*>& moves, bool debug);
    void getAllPossibleMoveMa(int sid, Vector<Move*>& moves, bool debug);
    void getAllPossibleMovePao(int sid, Vector<Move*>& moves, bool debug);
    void getAllPossibleMoveBing(int sid, Vector<Move*>& moves, bool debug);
    void getAllPossibleMoveJiang(int sid, Vector<Move*>& moves, bool debug);
    void getAllPossibleMoveShi(int sid, Vector<Move*>& moves, bool debug);
    void getAllPossibleMoveXiang(int sid, Vector<Move*>& moves, bool debug);
    
    void fakeMove(Move* move);
    void unfakeMove(Move* move);
    int calcScore();
    int getMinScore(int level, int cur);
    int getMaxScore(int level, int cur);
    
};
#endif /* defined(____T28Chess__) */
