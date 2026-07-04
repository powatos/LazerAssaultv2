
#include <Core/Control/GameInstance.hpp>
#include <UI/Widgets/TextElement.hpp>

#include "LazerAssaultGM.hpp"
#include "InfoDisplay.hpp"

InfoDisplay::InfoDisplay(std::string UID) : Widget(UID) {

    auto healthDisplay = AddElement<TextElement>("healthDisplay");
    auto scoreDisplay = AddElement<TextElement>("scoreDisplay");

    // Screen positions originate from the top-left of the widget
    healthDisplay->SetScreenPosition(Vector2(0,0));
    scoreDisplay->SetScreenPosition(Vector2(0,1));

    healthDisplay->SetVisibility(true);
    scoreDisplay->SetVisibility(true);

    SetScreenSize(Vector2(20,4));
    SetScreenPosition(Vector2());

    SetVisibility(true);
}

void InfoDisplay::TickPostUpdate(float dt) {
    auto gameInstance = GameInstance::Get();
    auto player = gameInstance->GetPlayerController()->GetPlayer();

    auto gm = dynamic_cast<LazerAssaultGM*>(gameInstance->GetGamemode());

    auto healthDisplay = dynamic_cast<TextElement*>(GetElement("healthDisplay"));
    auto scoreDisplay = dynamic_cast<TextElement*>(GetElement("scoreDisplay"));

    // nullptr check
    if (!(healthDisplay && scoreDisplay && gm)) { return; }

    float health = player->GetHealth();
    int score = gm->GetScore();

    healthDisplay->field = "Health: " + std::to_string(health);
    scoreDisplay->field = "Score: " + std::to_string(score);
}