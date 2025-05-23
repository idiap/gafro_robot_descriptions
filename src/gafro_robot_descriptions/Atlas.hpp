// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

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
    class Atlas : public System<T>
    {
      public:
        Atlas();

        Atlas(const std::filesystem::path &assets_folder);

        virtual ~Atlas();

      protected:
      private:
    };

    template <class T>
    Atlas<T>::Atlas()  //
      : System<T>(std::move(SystemSerialization(FilePath("robots/atlas/atlas.yaml")).load().cast<T>()))
    {}

    template <class T>
    Atlas<T>::Atlas(const std::filesystem::path &assets_folder)
      : System<T>(std::move(SystemSerialization(FilePath(assets_folder / "robots/atlas/atlas.yaml")).load().cast<T>()))
    {}

    template <class T>
    Atlas<T>::~Atlas()
    {}

}  // namespace gafro