#pragma once
#include "Framework/Common/Singleton.h"

class GameManager : public Sample::Singleton<GameManager> {
    friend class Sample::Singleton<GameManager>;

private:

    int enemyDeadCount_;

    bool isGameClear_;
    bool isGameOver_;

public:
    GameManager() : enemyDeadCount_(0), isGameClear_(false), isGameOver_(false) {}

    ~GameManager() {}

    void Reset() { enemyDeadCount_ = 0; isGameClear_ = false; isGameOver_ = false; }

    void AddEnemyDeadCount() { enemyDeadCount_++; }
    int EnemyDeadCount() { return enemyDeadCount_; }

    void IsGameClear(bool b) { isGameClear_ = b; }
    bool IsGameClear() const { return isGameClear_; }
    void IsGameOver(bool b) { isGameOver_ = b; }
    bool IsGameOver() const { return isGameOver_; }
};

#define GameManagerInstance GameManager::GetInstance()