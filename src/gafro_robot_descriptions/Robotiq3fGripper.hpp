// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <gafro/robot/Hand.hpp>
//
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>
//
#include <filesystem>

namespace gafro
{

    template <class T>
    class Robotiq3fGripper : public Hand<T, 4, 4, 3>
    {
      public:
        Robotiq3fGripper();

        Robotiq3fGripper(const std::filesystem::path &assets_folder);

        virtual ~Robotiq3fGripper();

      protected:
      private:
    };

    template <class T>
    Robotiq3fGripper<T>::Robotiq3fGripper()  //
      : Hand<T, 4, 4, 3>(std::move(SystemSerialization(FilePath("robots/robotiq/3fGripper/robotiq-3f-gripper.yaml")).load().cast<T>()),
                         { "finger_1_joint_3", "finger_2_joint_3", "finger_middle_joint_3" })
    {}

    template <class T>
    Robotiq3fGripper<T>::Robotiq3fGripper(const std::filesystem::path &assets_folder)
      : Hand<T, 4, 4, 3>(
          std::move(SystemSerialization(FilePath(assets_folder / "robots/robotiq/3fGripper/robotiq-3f-gripper.yaml")).load().cast<T>()),
          { "finger_1_joint_3", "finger_2_joint_3", "finger_middle_joint_3" })
    {}

    template <class T>
    Robotiq3fGripper<T>::~Robotiq3fGripper()
    {}

}  // namespace gafro