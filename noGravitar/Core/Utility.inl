//
//  Utility.inl
//  noGravitar
//
//  Created by Giovanni Basso on 09/06/21.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}
