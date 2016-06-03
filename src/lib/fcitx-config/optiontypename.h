/*
 * Copyright (C) 2015~2015 by CSSlayer
 * wengxt@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef _FCITX_CONFIG_TYPENAME_H_
#define _FCITX_CONFIG_TYPENAME_H_

#include <string>
#include <fcitx-utils/key.h>
#include <fcitx-utils/color.h>

namespace fcitx {

#define FCITX_SPECIALIZE_TYPENAME(TYPE, NAME)                                  \
    static inline std::string configTypeNameHelper(TYPE *) { return NAME; }

FCITX_SPECIALIZE_TYPENAME(bool, "Boolean");
FCITX_SPECIALIZE_TYPENAME(int, "Integer");
FCITX_SPECIALIZE_TYPENAME(std::string, "String");
FCITX_SPECIALIZE_TYPENAME(fcitx::Key, "Key");
FCITX_SPECIALIZE_TYPENAME(fcitx::Color, "Color");

template <typename T, typename = void>
struct OptionTypeName {
    static std::string get() {
        using ::fcitx::configTypeNameHelper;
        return configTypeNameHelper(static_cast<T *>(nullptr));
    }
};

template <typename T>
struct OptionTypeName<std::vector<T>> {
    static std::string get() { return "List|" + OptionTypeName<T>::get(); }
};

template <typename T>
struct OptionTypeName<T,
                      typename std::enable_if<std::is_enum<T>::value>::type> {
    static std::string get() { return "Enum"; }
};
}

#endif // _FCITX_CONFIG_TYPENAME_H_