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
    class FrankaEmikaRobot : public Manipulator<T, 7>
    {
      public:
        FrankaEmikaRobot();

        FrankaEmikaRobot(const std::filesystem::path &assets_folder);

        virtual ~FrankaEmikaRobot();

      protected:
      private:
    };

    template <class T>
    FrankaEmikaRobot<T>::FrankaEmikaRobot()  //
      : Manipulator<T, 7>(std::move(SystemSerialization(FilePath("robots/panda/panda.yaml")).load().cast<T>()), "panda_endeffector_joint")
    {}

    template <class T>
    FrankaEmikaRobot<T>::FrankaEmikaRobot(const std::filesystem::path &assets_folder)
      : Manipulator<T, 7>(std::move(SystemSerialization(FilePath(assets_folder / "robots/panda/panda.yaml")).load().cast<T>()),
                          "panda_endeffector_joint")
    {}

    template <class T>
    FrankaEmikaRobot<T>::~FrankaEmikaRobot()
    {}

}  // namespace gafro