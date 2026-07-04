#pragma once

#include <Core/Control/Gamemode.hpp>

class Block;

class LazerAssaultGM : public Gamemode
{
public:
    LazerAssaultGM();
    void BeginPlay() override;

    int GetScore() const;

private:
    float flashDelay;
    int score;

    std::vector<Block*> lazerList;

    void SpawnLazer();
    void damagePlayer();

    void StartWave();
    void FlashLazers(int currentIteration, const int totalIterations, bool bOn);
    void ActivateLazers();
    void EndWave();

};