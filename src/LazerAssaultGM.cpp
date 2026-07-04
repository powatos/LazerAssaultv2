
#include <Util/TimerManager.hpp>
#include <Game/Actors/Block.hpp>
#include <Core/Control/GameInstance.hpp>

#include <Util/GameplayHelper.hpp>

#include "LazerAssaultGM.hpp"

SET_DEFAULT_SUBCLASS(Gamemode, LazerAssaultGM)

LazerAssaultGM::LazerAssaultGM() {
    flashDelay = 0.2f;
    score = 0;
}

int LazerAssaultGM::GetScore() const {
    return score;
}

void LazerAssaultGM::BeginPlay() {
    auto timerManager = TimerManager::Get();

    timerManager->AddTimer(
        "gameStartDelay",
        3.0,
        this,
        &LazerAssaultGM::StartWave
    );

}

void LazerAssaultGM::StartWave() {

    SpawnLazer();

    for (auto lazer : lazerList) {
        bool b = GameplayHelper::RandomBool(); // horizontal or vertical
        if (b) {
            // horizontal

            lazer->ctex = '-'; // set texture to repeat horizontally
            lazer->SetSize( Vector2(100,1) );
            lazer->SetPosition(Vector2(0, GameplayHelper::RandomInt(0,23)));
        } else {
            // vertical

            lazer->ctex = '|'; // set texture to repeat vertically
            lazer->SetSize( Vector2(1,100) );
            lazer->SetPosition(Vector2(GameplayHelper::RandomInt(0,80), 23));
        }
    }


    auto timerManager = TimerManager::Get();
    timerManager->AddTimer(
        "initFlash",
        flashDelay,
        this,
        &LazerAssaultGM::FlashLazers,
        0, 7, true
    );

}

void LazerAssaultGM::SpawnLazer() {
    auto world = GameInstance::Get()->GetWorld();

    auto lazer = world->SpawnActor<Block>();
    lazer->SetMovability(ActorMovability::Static);
    lazer->SetSimulatingPhysics(false);
    lazer->SetVisibility(false);
    lazer->SetCollisionType(CollisionType::None);
    
    lazerList.push_back(lazer);

}

void LazerAssaultGM::FlashLazers(int currentIteration, const int totalIterations, bool bOn) {

    if (currentIteration >= totalIterations) {
        ActivateLazers();
        return;
    }

    for (auto lazer : lazerList) {
        lazer->SetVisibility(bOn);
    }

    bOn = !bOn;
    currentIteration++;
    
    auto timerManager = TimerManager::Get();
    timerManager->AddTimer("flash",
        flashDelay,
        this,
        &LazerAssaultGM::FlashLazers,
        currentIteration, totalIterations, bOn
    );

}

void LazerAssaultGM::ActivateLazers() {
    auto player = GameInstance::Get()->GetPlayerController()->GetPlayer();

    for (auto lazer : lazerList) {
        if (GameplayHelper::IsActorOverlapping(player, lazer)) {
            damagePlayer();
        }
    }

    auto timerManager = TimerManager::Get();
    timerManager->AddTimer(
        "waveEndDelay",
        1.0,
        this,
        &LazerAssaultGM::EndWave
    );
    
}

void LazerAssaultGM::damagePlayer() {
    auto gameInstance = GameInstance::Get();
    auto player = gameInstance->GetPlayerController()->GetPlayer();

    player->TakeDamage(10);
    if (player->GetHealth() <= 0.f) {
        gameInstance->RequestShutdown();
    }

}

void LazerAssaultGM::EndWave() {

    for (auto lazer : lazerList) {
        lazer->SetVisibility(false);
    }

    score++;

    auto timerManager = TimerManager::Get();
    timerManager->AddTimer(
        "waveDelay",
        2.0,
        this,
        &LazerAssaultGM::StartWave
    );

}