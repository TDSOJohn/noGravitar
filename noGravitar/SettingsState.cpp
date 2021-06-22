//
//  SettingsState.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 09/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "SettingsState.hpp"
#include "Core/Utility.hpp"
#include "Core/ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context):
    State(stack, context),
    mGUIContainer()
{
//    mBackgroundSprite.setTexture(context.textures->get(Textures::ssBackground));
    
    // Build key binding buttons and labels
    addButtonLabel(Player::MoveUp,      150.f, "Move Up", context);
    addButtonLabel(Player::MoveLeft,    250.f, "Move Left", context);
    addButtonLabel(Player::MoveDown,    350.f, "Move Down", context);
    addButtonLabel(Player::MoveRight,   450.f, "Move Right", context);
    addButtonLabel(Player::Fire,        550.f, "Fire", context);
    addButtonLabel(Player::UseHook,     650.f, "Use Hook", context);
    addButtonLabel(Player::LaunchMissile, 750.f, "Launch Missile", context);

    updateLabels();

    auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backButton->setPosition(context.window->getView().getSize().x - 428, 700.f);
    backButton->setText("Back");
    backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

    mGUIContainer.pack(backButton);
}


void SettingsState::draw()
{
    sf::RenderWindow& window = *getContext().window;

//    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}


bool SettingsState::update(sf::Time)
{
    return true;
}


bool SettingsState::handleEvent(const sf::Event& event)
{
    bool isKeyBinding = false;
    
    // Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
    for (std::size_t action = 0; action < Player::ActionCount; ++action)
    {
        if (mBindingButtons[action]->isActive())
        {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased)
            {
                getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
                mBindingButtons[action]->deactivate();
            }
            break;
        }
    }

    // If pressed button changed key bindings, update labels; otherwise consider other buttons in container
    if (isKeyBinding)
        updateLabels();
    else
        mGUIContainer.handleEvent(event);

    return false;
}


void SettingsState::updateLabels()
{
    Player& player = *getContext().player;

    for (std::size_t i = 0; i < Player::ActionCount; ++i)
    {
        sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
        mBindingLabels[i]->setText(toString(key));
    }
}


void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
    mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    mBindingButtons[action]->setPosition(300.f, y);
    mBindingButtons[action]->setText(text);
    mBindingButtons[action]->setToggle(true);

    mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
    mBindingLabels[action]->setPosition(450.f, y + 32.f);

    mGUIContainer.pack(mBindingButtons[action]);
    mGUIContainer.pack(mBindingLabels[action]);
}
