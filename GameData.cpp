#include "GameData.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

GameData::GameData() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            num[i][j] = 0;
    my_best = score = 0;
}

int GameData::GetPositionNumber(int x, int y) {
    return this->num[x][y];
}

void GameData::ChangePositionNumber(int x, int y, int p) {
    num[x][y] = p;
}

int GameData::GetScore() {
    return this->score;
}

int GameData::GetBestScore() {
    return this->my_best;
}

bool GameData::IsGameOver() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (num[i][j] == 0)return false;
            if (i - 1 >= 0 && num[i - 1][j] == num[i][j])return false;
            if (i + 1 < 4 && num[i + 1][j] == num[i][j])return false;
            if (j - 1 >= 0 && num[i][j - 1] == num[i][j])return false;
            if (j + 1 < 4 && num[i][j + 1] == num[i][j])return false;
        }
    }
    my_best = std::max(my_best, score);
    std::ofstream TempFile("2048GAME.data",std::ios::out | std::ios::binary);
    if(TempFile.is_open())
        TempFile<<my_best;
    else
        std::cout<<"存储最佳分数失败！"<<std::endl;
    TempFile.close();
    return true;
}

void GameData::SetBestRecord(std::string name, int bscore) {
    if (name.empty())local_name = "None";
    local_best = bscore;
}

void GameData::MakeNewNumber() {
    std::vector<std::pair<int, int> > t;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (num[i][j] == 0)t.push_back(std::make_pair(i, j));
        }
    }
    if (t.size() == 0)return;
    int fillnum;
    if (rand() % 2)fillnum = 2;
    else fillnum = 4;
    int trand = rand() % t.size();
    ChangePositionNumber(t[trand].first, t[trand].second, fillnum);
}

void GameData::InitNewGame() {
    local_best = std::max(local_best, score);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            num[i][j] = 0;
    MakeNewNumber();
    MakeNewNumber();
    std::ifstream TempFile("2048GAME.data",std::ios::in | std::ios::binary);
    if(TempFile.is_open())
        TempFile>>my_best;
    TempFile.close();
    score = 0;
}

void GameData::AddScore(int add_num) {
    this->score += add_num;
}
