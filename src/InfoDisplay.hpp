#pragma once

#include <UI/Widgets/Widget.hpp>

class InfoDisplay : public Widget
{
public:

    InfoDisplay(std::string UID);
    void TickPostUpdate(float dt) override;
    
};