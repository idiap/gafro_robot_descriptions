// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <gafro/robot/Humanoid.hpp>
//
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>
//
#include <filesystem>

namespace gafro
{

    template <class T>
    class UnitreeG1 : public Humanoid<T>
    {
      public:
        UnitreeG1();

        UnitreeG1(const std::filesystem::path &assets_folder);

        virtual ~UnitreeG1();

      protected:
      private:
    };

    template <class T>
    UnitreeG1<T>::UnitreeG1()  //
      : Humanoid<T>(std::move(SystemSerialization(FilePath("robots/unitree/g1/g1.yaml")).load().cast<T>()))
    {}

    template <class T>
    UnitreeG1<T>::UnitreeG1(const std::filesystem::path &assets_folder)
      : Humanoid<T>(std::move(SystemSerialization(FilePath(assets_folder / "robots/unitree/g1/g1.yaml")).load().cast<T>()))
    {}

    template <class T>
    UnitreeG1<T>::~UnitreeG1()
    {}

}  // namespace gafro