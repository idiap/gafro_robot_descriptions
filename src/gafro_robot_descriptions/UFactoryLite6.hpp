// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <gafro/robot/Manipulator.hpp>
//
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>
//
#include <filesystem>

namespace gafro
{

    template <class T>
    class UFactoryLite6 : public Manipulator<T, 6>
    {
      public:
        UFactoryLite6();

        UFactoryLite6(const std::filesystem::path &assets_folder);

        virtual ~UFactoryLite6();

      protected:
      private:
    };

    template <class T>
    UFactoryLite6<T>::UFactoryLite6()  //
      : Manipulator<T, 6>(std::move(SystemSerialization(FilePath("robots/ufactory/lite6/lite6.yaml")).load().cast<T>()), "lite6_joint_eef")
    {}

    template <class T>
    UFactoryLite6<T>::UFactoryLite6(const std::filesystem::path &assets_folder)
      : Manipulator<T, 6>(std::move(SystemSerialization(FilePath(assets_folder / "robots/ufactory/lite6/lite6.yaml")).load().cast<T>()),
                          "lite6_joint_eef")
    {}

    template <class T>
    UFactoryLite6<T>::~UFactoryLite6()
    {}

}  // namespace gafro