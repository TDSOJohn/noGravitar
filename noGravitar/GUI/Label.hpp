//
//  Label.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 08/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp


#include "Component.hpp"

#include "../Core/ResourceHolder.hpp"
#include "../ResourceIdentifiers.hpp"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> Ptr;
            

    public:
                            Label(const std::string& text, const FontHolder& fonts);

        virtual bool        isSelectable() const;
        void                setText(const std::string& text);

        virtual void        handleEvent(const sf::Event& event);


    private:
        void                draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text            mText;
};

}

#endif /* Label_hpp */
