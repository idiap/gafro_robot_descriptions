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
    class UR5 : public Manipulator<T, 6>
    {
      public:
        UR5();

        UR5(const std::filesystem::path &assets_folder);

        virtual ~UR5();

      protected:
      private:
    };

    template <class T>
    UR5<T>::UR5()  //
      : Manipulator<T, 6>(std::move(SystemSerialization(FilePath("robots/ur5/ur5.yaml")).load().cast<T>()), "wrist_3_link-tool0_fixed_joint")
    {}

    template <class T>
    UR5<T>::UR5(const std::filesystem::path &assets_folder)
      : Manipulator<T, 6>(std::move(SystemSerialization(FilePath(assets_folder / "robots/ur5/ur5.yaml")).load().cast<T>()),
                          "wrist_3_link-tool0_fixed_joint")
    {}

    template <class T>
    UR5<T>::~UR5()
    {}

}  // namespace gafro