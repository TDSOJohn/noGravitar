//
//  SettingsState.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 09/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef SettingsState_hpp
#define SettingsState_hpp

#include "Core/State.hpp"
#include "Player.hpp"
#include "GUI/Container.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
    public:
                                        SettingsState(StateStack& stack, Context context);

        virtual void                    draw();
        virtual bool                    update(sf::Time dt);
        virtual bool                    handleEvent(const sf::Event& event);


    private:
        void                            updateLabels();
        void                            addButtonLabel(Player::Action action, float y, const std::string& text, Context context);


    private:
        sf::Sprite                                            mBackgroundSprite;
        GUI::Container                                       mGUIContainer;
        std::array<GUI::Button::Ptr, Player::ActionCount>    mBindingButtons;
        std::array<GUI::Label::Ptr, Player::ActionCount>     mBindingLabels;
};



#endif /* SettingsState_hpp */
