
#include <Core/PotatoEngine.hpp>
#include <Core/Control/GameInstance.hpp>
#include <Core/Input/InputController.hpp>

#include "CharacterController.hpp"

SET_DEFAULT_SUBCLASS(PlayerController, CharacterController)

CharacterController::CharacterController() {
    moveSpeed = 1.f;
    CameraFollowsPlayer = false;
}

void CharacterController::SetupInputBindings() {

    auto InputController = PotatoEngine::Get().GetInputController();

    InputController->RegisterInputBinding({
        InputBinding(Keycode::W, InputType::Impulse, "moveup", this, &CharacterController::moveup),
        InputBinding(Keycode::A, InputType::Impulse, "moveleft", this, &CharacterController::moveleft),
        InputBinding(Keycode::S, InputType::Impulse, "movedown", this, &CharacterController::movedown),
        InputBinding(Keycode::D, InputType::Impulse, "moveright", this, &CharacterController::moveright)
    });

}

void CharacterController::moveup() {
    GetPlayer()->AddLocalOffset(Vector2::Up() * moveSpeed);
}
void CharacterController::moveleft() {
    GetPlayer()->AddLocalOffset(-Vector2::Right() * moveSpeed);
}
void CharacterController::movedown() {
    GetPlayer()->AddLocalOffset(-Vector2::Up() * moveSpeed);
}
void CharacterController::moveright() {
    GetPlayer()->AddLocalOffset(Vector2::Right() * moveSpeed);
}