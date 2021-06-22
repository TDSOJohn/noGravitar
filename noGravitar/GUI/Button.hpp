//
//  Button.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 09/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include "Component.hpp"

#include "../Core/ResourceHolder.hpp"
#include "../ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>



namespace GUI
{

class Button : public Component
{
    public:
        typedef std::shared_ptr<Button>     Ptr;
        typedef std::function<void()>       Callback;


    public:
                                Button(const FontHolder& fonts, const TextureHolder& textures);

        void                    setCallback(Callback callback);
        void                    setText(const std::string& text);
        void                    setToggle(bool flag);

        virtual bool            isSelectable() const;
        virtual void            select();
        virtual void            deselect();

        virtual void            activate();
        virtual void            deactivate();

        virtual void            handleEvent(const sf::Event& event);


    private:
        virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Callback                mCallback;
        const sf::Texture&      mNormalTexture;
        const sf::Texture&      mSelectedTexture;
        const sf::Texture&      mPressedTexture;
        sf::Sprite              mSprite;
        sf::Text                mText;
        bool                    mIsToggle;
};

}

#endif /* Button_hpp */
