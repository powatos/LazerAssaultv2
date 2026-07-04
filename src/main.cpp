
#include <Core/PotatoEngine.hpp>
#include <Core/Control/GameInstance.hpp>
#include <Core/Data/PersistentLevel.hpp>
#include <UI/HUDController.hpp>

#include "InfoDisplay.hpp"
#include "CharacterController.hpp"

int main()
{
    auto& engine = PotatoEngine::Get();
    engine.LoadSubclasses();

    auto* gameInstance = GameInstance::Get();

    gameInstance->FRAMES_PER_SECOND = 24.f;
    gameInstance->MS_REPEAT_THRESHOLD = 195;

    PersistentLevel level("save.json");
    level.LoadStaticActors();

    auto* world = gameInstance->GetWorld();
    world->Settings.doGravity = false;
    world->Settings.clipAllowed = 0.f;
    world->Settings.Size = Vector2(80,24); // terminal window size

    auto* HUDController = engine.GetHUDController();
    HUDController->AddWidget<InfoDisplay>("main info display");

    auto* PC = gameInstance->GetPlayerController();
    auto* player = PC->GetPlayer();

    player->ctex = 'X';
    player->SetUsingCTex(true);
    player->SetSize(Vector2(1,1));

    engine.BeginPlay();
    engine.Resolve();

    return 0;
}