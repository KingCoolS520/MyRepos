//
//  T28Chess.cpp
//  
//
//  Created by 薛国良 on 15/11/22.
//
//

#include "T28Chess.h"

bool T28Chess::init()
{
    Layer::init();
    
    // 常量和中间变量的初始化
    _selectid = -1;
    _d = 32;
    _off = Vec2(113, 16);
    _bRedTurn = true;
    
    auto winSize = Director::getInstance()->getWinSize();
    // 创建棋盘
    Sprite* plate = Sprite::create("chess/background.png");
    addChild(plate);
    plate->setPosition(winSize/2);
    
    auto size = plate->getContentSize();
    float s1 = winSize.height/size.height;
    float s2 = winSize.width/size.width;
    float s = s1 < s2 ? s1 : s2;
    plate->setScale(s);
    
    for(int row = 0; row<=9; ++row)
    {
        for(int col=0; col<=8; ++col)
        {
            _stoneids[row][col] = -1;
        }
    }
    
    // 32 Stones
    for(int i=0; i<32; ++i)
    {
        _stone[i] = Stone::create(i);
        addChild(_stone[i]);
        _stone[i]->setScale(_d/_stone[i]->getContentSize().width);
        
        int x = _stone[i]->_col * _d;
        int y = _stone[i]->_row * _d;
        Vec2 pos = _off + Vec2(x, y);
        _stone[i]->setPosition(pos);
        
        _stoneids[_stone[i]->_row][_stone[i]->_col] = i;
    }
    
    
    
    _selectedFlag = Sprite::create("chess/selected.png");
    addChild(_selectedFlag);
    _selectedFlag->setVisible(false);
    _selectedFlag->setScale(_d/_selectedFlag->getContentSize().width);
    
    // touch处理
    auto ev = EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [](Touch*, Event*){return true;};
    ev->onTouchEnded = [&](Touch* touch, Event*)
    {
        if(this->_selectid == -1)
        {
            selectStone(touch);
        }
        else
        {
            moveStone(touch);
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    
    
    return true;
}

void T28Chess::selectStone(cocos2d::Touch *touch)
{
    // 黑棋由电脑来移动，所以黑棋走时，不再让选中棋子
    if(!this->_bRedTurn)
        return;
    
    Vec2 pos = touch->getLocation();
    for(int i=0; i<32; ++i)
    {
        Stone* s = _stone[i];
        if(s->_dead) continue;
        
        if(s->getPosition().getDistance(pos) < _d/2 && s->_color == this->_bRedTurn)
        {
            _selectid = i;
            _selectedFlag->setPosition(s->getPosition());
            _selectedFlag->setVisible(true);
            return;
        }
    }
}

void T28Chess::moveStone(cocos2d::Touch *touch)
{
    Vec2 pos = touch->getLocation(); // 屏幕坐标
    pos -= _off; // 转化成棋盘的像素坐标
    Stone* s = _stone[_selectid];
    
    // 转化成棋盘格子坐标
    int row = (pos.y + _d/2) / _d;
    int col = (pos.x + _d/2) / _d;
    
    
    int killid = -1;
    
    // 检查目标位置的棋子
    for(int i=0; i<32; ++i)
    {
        Stone* skill = _stone[i];
        if(skill->_dead) continue;
        
        if(skill->_row == row && skill->_col == col)
        {
            if(skill->_color == this->_bRedTurn)
            {
                selectStone(touch);
                return;
            }
            
            killid = i;
            break;
        }
    }
    
    // 判断
    if(!canMove(_selectid, killid, row, col))
    {
        return;
    }
    
    _stoneids[s->_row][s->_col] = -1;
    _stoneids[row][col] = s->_stoneId;
    
    // 吃子
    if(killid != -1)
    {
        Stone* skill = _stone[killid];
        skill->_dead = true;
        skill->setVisible(false);
    }
    
    // 移动
    s->_row = row;
    s->_col = col;
    s->setPosition(Vec2(_d* col, _d* row) + _off);
    
    // 恢复中间变量，记录局面信息
    _selectid = -1;
    _bRedTurn = !_bRedTurn; // 下一步对方走
    _selectedFlag->setVisible(false);
    
    // 如果下一步是黑棋
    if(_bRedTurn == false)
    {
        ComputerMove(6);
    }
}

int T28Chess::getStoneId(int row, int col)
{
    return _stoneids[row][col];
}

bool T28Chess::canMove(int moveid, int killid, int row, int col)
{
    Stone* s = _stone[moveid];
    if(killid != -1)
    {
        Stone* k = _stone[killid];
        if(s->_color == k->_color)
            return false;
    }
    
    switch (s->_type) {
        case Stone::CHE:
            return canMoveCHE(moveid, killid, row, col);
        case Stone::MA:
            return canMoveMA(moveid, killid, row, col);
        case Stone::PAO:
            return canMovePAO(moveid, killid, row, col);
        case Stone::JIANG:
            return canMoveJIANG(moveid, killid, row, col);
        case Stone::SHI:
            return canMoveSHI(moveid, killid, row, col);
        case Stone::XIANG:
            return canMoveXIANG(moveid, killid, row, col);
        case Stone::BING:
            return canMoveBING(moveid, killid, row, col);
        default:
            break;
    }
    
    return false;
}

int T28Chess::getStoneCount(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if( row1 != row2 && col1 != col2)
        return -1;
    
    if(row1 == row2)
    {
        // 遍历col1到col2
        int min = col1 < col2 ? col1 : col2;
        int max = col1 > col2 ? col1 : col2;
        for(int col = min+1 ; col < max; col ++)
        {
            int id = getStoneId(row1, col);
            if(id != -1) ret++;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 > row2 ? row1 : row2;
        for(int row = min+1 ; row < max; row ++)
        {
            int id = getStoneId(row, col1);
            if(id != -1) ret++;
        }
    }
    
    return ret;
}

bool T28Chess::canMoveCHE(int moveid, int killid, int row, int col)
{
    Stone* s = _stone[moveid];
    int ret = getStoneCount(s->_row, s->_col, row, col);
    
    return ret == 0;
}

bool T28Chess::canMoveMA(int moveid, int killid, int row, int col)
{
    Stone* s = _stone[moveid];
    int d = abs(s->_row - row) * 10 + abs(s->_col - col);
    if(d == 21 || d == 12)
    {
        // 马腿
        int r;
        int c;
        if(d == 21)
        {
            r = (s->_row + row) / 2;
            c = s->_col;
        }
        else
        {
            r = s->_row;
            c = (s->_col + col) /2;
        }
        
        int id = getStoneId(r, c);
        
        // 马腿上有棋子
        if(id != -1) return false;
        
        return true;
    }
    
    return false;
}

bool T28Chess::canMovePAO(int moveid, int killid, int row, int col)
{
    Stone* s = _stone[moveid];
    int ret = getStoneCount(s->_row, s->_col, row, col);
    if(killid == -1)
    {
        return ret == 0;
    }
    
    return ret == 1;
}

bool T28Chess::canMoveJIANG(int moveid, int killid, int row, int col)
{
    if(killid != -1)
    {
        if(_stone[killid]->_type == Stone::JIANG)
        {
            return canMoveCHE(moveid, killid, row, col);
        }
    }
    
    Stone* s = _stone[moveid];
    if(col < 3) return false;
    if(col > 5) return false;
    if(row > 2 && s->_color) return false;
    if(row < 7 && !s->_color) return false;
    
    int d = abs(s->_row - row) * 10 + abs(s->_col - col);
    if(d == 1 || d == 10)
        return true;
    return false;
}

bool T28Chess::canMoveSHI(int moveid, int killid, int row, int col)
{
    Stone* s = _stone[moveid];
    if(col < 3) return false;
    if(col > 5) return false;
    if(row > 2 && s->_color) return false;
    if(row < 7 && !s->_color) return false;
    
    int d = abs(s->_row - row) * 10 + abs(s->_col - col);
    if(d == 11)
        return true;
    return false;
}

bool T28Chess::canMoveXIANG(int moveid, int killid, int row, int col)
{
    Stone* s = _stone[moveid];
    
    if(row > 4 && s->_color) return false;
    if(row < 5 && !s->_color) return false;
    
    int d = abs(s->_row - row) * 10 + abs(s->_col - col);
    if(d == 22)
    {
        int r = (s->_row + row)/2;
        int c = (s->_col + col)/2;
        if(getStoneId(r, c) == -1)
        {
            return true;
        }
    }
    return false;
}

bool T28Chess::canMoveBING(int moveid, int killid, int row, int col)
{
    Stone* s = _stone[moveid];
    int d = abs(s->_row - row) * 10 + abs(s->_col - col);
    if(d != 1 && d != 10)
    {
        return false;
    }
    
    if(s->_color)
    {
        // 不能后退
        if(row < s->_row) return false;
        
        // 没过河不能横着走
        if (s->_row < 5 && row == s->_row) {
            return false;
        }
        
        return true;
    }
    else
    {
        // 不能后退
        if(row > s->_row) return false;
        
        // 没过河不能横着走
        if (s->_row > 4 && row == s->_row) {
            return false;
        }
        
        return true;
    }
}

void T28Chess::getAllPossibleMoveXiang(int sid, Vector<Move *> &moves, bool debug)
{
    Stone* s = _stone[sid];
    int row = s->_row;
    int col = s->_col;
    
    int rowTo;
    int colTo;
    
    rowTo = row + 2;
    colTo = col + 2;
    if(rowTo <= 9 && colTo <= 8)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row - 2;
    colTo = col - 2;
    if(rowTo >=0 && colTo >=0)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row + 2;
    colTo = col - 2;
    if(rowTo <=9 && colTo >=0)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row - 2;
    colTo = col + 2;
    if(rowTo >=0 && colTo <=8)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
}

void T28Chess::getAllPossibleMoveShi(int sid, Vector<Move *> &moves, bool debug)
{
    Stone* s = _stone[sid];
    int row = s->_row;
    int col = s->_col;
    
    int rowTo;
    int colTo;
    
    rowTo = row + 1;
    colTo = col + 1;
    if(rowTo <= 9 && colTo <= 8)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row - 1;
    colTo = col - 1;
    if(rowTo >=0 && colTo >=0)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row + 1;
    colTo = col - 1;
    if(rowTo <=9 && colTo >=0)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row - 1;
    colTo = col + 1;
    if(rowTo >=0 && colTo <=8)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
}
void T28Chess::getAllPossibleMoveChe(int sid, Vector<Move *> &moves, bool debug)
{
    Stone* s = _stone[sid];
    int row = s->_row;
    int col = s->_col;
    
    int rowTo;
    int colTo;
    
    colTo = col;
    for(int rowTo = 0; rowTo <= 9; ++rowTo)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row;
    for(int colTo = 0; colTo <= 8; ++colTo)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
}

void T28Chess::getAllPossibleMoveJiang(int sid, Vector<Move *> &moves, bool debug)
{
    Stone* s = _stone[sid];
    int row = s->_row;
    int col = s->_col;
    
    int rowTo;
    int colTo;
    
    if(debug)
    {
        int forbreak;
        forbreak = 0;
    }
    
    rowTo = row + 1;
    colTo = col;
    if(rowTo <= 9)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            if(debug)
                CCLOG("Jiang can move to %d, %d", rowTo, colTo);
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row - 1;
    colTo = col;
    if(rowTo >=0 )
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            if(debug)
                CCLOG("Jiang can move to %d, %d", rowTo, colTo);
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row;
    colTo = col + 1;
    if(colTo <= 8)
    {
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            if(debug)
                CCLOG("Jiang can move to %d, %d", rowTo, colTo);
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
    
    rowTo = row;
    colTo = col - 1;
    if(colTo >= 0)
    {
        
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            if(debug)
                CCLOG("Jiang can move to %d, %d", rowTo, colTo);
            
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
}

void T28Chess::getAllPossibleMoveMa(int sid, Vector<Move *> &moves, bool debug)
{
    Stone* s = _stone[sid];
    int row = s->_row;
    int col = s->_col;
    
    int rowTos[] = {row+2, row+2, row-2, row-2, row+1, row+1, row-1, row-1};
    int colTos[] = {col+1, col-1, col+1, col-1, col+2, col-2, col+2, col-2};
    
    for(int i=0; i<8; ++i)
    {
        int rowTo = rowTos[i];
        int colTo = colTos[i];
        
        if(rowTo < 0) continue;
        if(rowTo > 9) continue;
        if(colTo < 0) continue;
        if(colTo > 8) continue;
        
        if (canMove(sid, getStoneId(rowTo, colTo), rowTo, colTo))
        {
            Move* move = Move::create(sid, getStoneId(rowTo, colTo), rowTo, colTo, s->_row, s->_col);
            moves.pushBack(move);
        }
    }
}

void T28Chess::getAllPossibleMovePao(int sid, Vector<Move *> &moves, bool debug)
{
    getAllPossibleMoveChe(sid, moves, debug);
}

void T28Chess::getAllPossibleMoveBing(int sid, Vector<Move *> &moves, bool debug)
{
    getAllPossibleMoveJiang(sid, moves, false);
}
void T28Chess::getAllPossibleMove(Vector<Move *> &moves, bool debug)
{
    int min = 16;
    int max = 32;
    if(_bRedTurn)
        min = 0, max= 16;
        
    for(int i=min; i<max; ++i)
    {
        Stone* s = _stone[i];
        if (s->_dead)
        {
            continue;
        }
        
        switch (s->_type) {
            case Stone::CHE:
                getAllPossibleMoveChe(i, moves, debug);
                break;
            case Stone::MA:
                getAllPossibleMoveMa(i, moves, debug);
                break;
            case Stone::PAO:
                getAllPossibleMovePao(i, moves, debug);
                break;
            case Stone::BING:
                getAllPossibleMoveBing(i, moves, debug);
                break;
            case Stone::JIANG:
                getAllPossibleMoveJiang(i, moves, debug);
                break;
            case Stone::SHI:
                getAllPossibleMoveShi(i, moves, debug);
                break;
            case Stone::XIANG:
                getAllPossibleMoveXiang(i, moves, debug);
                break;
                
            default:
                break;
        }
        
#if 0
        // 粗暴
        for (int row = 0; row<=9; ++row)
        {
            for(int col=0; col<=8; ++col)
            {
                int kid = getStoneId(row, col);
                if(canMove(i, kid, row, col))
                {
                    Move* move = Move::create(i, kid, row, col, s->_row, s->_col);
                    moves.pushBack(move);
                }
            }
        }
#endif
        
    }
}

int T28Chess::getMaxScore(int level, int curMinScore)
{
    if(level == 0)
        return calcScore();
    
    Vector<Move*> possibleMoves;
    getAllPossibleMove(possibleMoves);
    
    int maxScore = -10000000;
    for (auto it = possibleMoves.begin(); it!=possibleMoves.end(); ++it)
    {
        Move* move = *it;
        
        fakeMove(move);
        int score = getMinScore(level-1, maxScore);
        unfakeMove(move);
        
        if(score >= curMinScore)
            return score;
        
        if (score > maxScore)
        {
            maxScore = score;
        }
    }
    return maxScore;
}

int T28Chess::getMinScore(int level, int curMaxScore)
{
    if(level == 0)
        return calcScore();
    
    Vector<Move*> possibleMoves;
    getAllPossibleMove(possibleMoves);
    
    int minScore = 10000000;
    
    for (auto it = possibleMoves.begin(); it!=possibleMoves.end(); ++it)
    {
        Move* move = *it;
        
        fakeMove(move);
        int score = getMaxScore(level-1, minScore);
        unfakeMove(move);
        
        if(score <= curMaxScore)
            return score;
        
        if (score < minScore)
        {
            minScore = score;
        }
    }
    return minScore;
}

void T28Chess::ComputerMove(int level)
{
    // 获取所有可能的移动情况
    Vector<Move*> possibleMoves;
    getAllPossibleMove(possibleMoves, true);
    
    // 计算所有可能的移动情况的结果
    // 比较哪个结果最好
    int maxScore = -10000000; // 负的无穷大
    Move* bestMove = nullptr;
    
    for (auto it = possibleMoves.begin(); it!=possibleMoves.end(); ++it)
    {
        Move* move = *it;
        
        // 对于每一个move，计算机要计算该Move移动后的局面情况
        
        int debugid = move->_moveid;
        Stone* debug = _stone[debugid];
        if(debug->_type == Stone::JIANG)
        {
            CCLOG("jinag");
        }
        fakeMove(move);
        // 指在这个局面下，得到一个最小值
        int score = getMinScore(level-1, maxScore);
        unfakeMove(move);
        
        if(score > maxScore)
        {
            maxScore = score;
            bestMove = move;
        }
    }
    
    // 使用bestMove来进行移动
    Stone* s = _stone[bestMove->_moveid];
    
    // 转化成棋盘格子坐标
    int row = bestMove->_row;
    int col = bestMove->_col;
    
    
    int killid = bestMove->_killid;
    
    _stoneids[s->_row][s->_col] = -1;
    _stoneids[row][col] = s->_stoneId;
    
    // 吃子
    if(killid != -1)
    {
        Stone* skill = _stone[killid];
        skill->_dead = true;
        skill->setVisible(false);
    }
    
    // 移动
    s->_row = row;
    s->_col = col;
    s->setPosition(Vec2(_d* col, _d* row) + _off);
    
    // 恢复中间变量，记录局面信息
    _selectid = -1;
    _bRedTurn = !_bRedTurn; // 下一步对方走
    _selectedFlag->setVisible(false);
}

// 核心
int T28Chess::calcScore()
{
    int bScore = 0;
    int rScore = 0;
    
    for(int i=0; i<16; ++i)
    {
        Stone* s = _stone[i];
        rScore += s->getScore();
    }
    
    for(int i=16; i<32; ++i)
    {
        Stone* s = _stone[i];
        bScore += s->getScore();
    }
    
    return bScore - rScore;
}

void T28Chess::fakeMove(Move *move)
{
    Stone* s = _stone[move->_moveid];
    if(move->_killid != -1)
    {
        Stone* k = _stone[move->_killid];
        k->_dead = true;
    }
    
    s->_row = move->_row;
    s->_col = move->_col;
    
    _stoneids[move->_rowFrom][move->_colFrom] = -1;
    _stoneids[move->_row][move->_col] = s->_stoneId;
    
    // 影响下一步的计算
    this->_bRedTurn = !_bRedTurn;
}

void T28Chess::unfakeMove(Move *move)
{
    Stone* s = _stone[move->_moveid];
    
    _stoneids[move->_rowFrom][move->_colFrom] = s->_stoneId;
    _stoneids[move->_row][move->_col] = -1;
    
    
    if(move->_killid != -1)
    {
        Stone* k = _stone[move->_killid];
        k->_dead = false;
        
        _stoneids[move->_row][move->_col] = k->_stoneId;
    }
    
    s->_row = move->_rowFrom;
    s->_col = move->_colFrom;
    
    this->_bRedTurn = !_bRedTurn;
}




