/*
    Copyright (c) 2022 Idiap Research Institute, http://www.idiap.ch/
    Written by Tobias Löw <https://tobiloew.ch>

    This file is part of gafro.

    gafro is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as
    published by the Free Software Foundation.

    gafro is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gafro. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <gafro/robot/System.hpp>
//
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>
//
#include <filesystem>

namespace gafro
{

    template <class T>
    class AnymalC : public System<T>
    {
      public:
        AnymalC();

        AnymalC(const std::filesystem::path &assets_folder);

        virtual ~AnymalC();

      protected:
      private:
    };

    template <class T>
    AnymalC<T>::AnymalC()  //
      : System<T>(std::move(SystemSerialization(FilePath("robots/anymal_c/anymal_c.yaml")).load().cast<T>()))
    {}

    template <class T>
    AnymalC<T>::AnymalC(const std::filesystem::path &assets_folder)
      : System<T>(std::move(SystemSerialization(FilePath(assets_folder / "robots/anymal_c/anymal_c.yaml")).load().cast<T>()))
    {}

    template <class T>
    AnymalC<T>::~AnymalC()
    {}

}  // namespace gafro