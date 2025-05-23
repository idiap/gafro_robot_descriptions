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
    class Planar3DoF : public Manipulator<T, 3>
    {
      public:
        Planar3DoF();

        Planar3DoF(const std::filesystem::path &assets_folder);

        virtual ~Planar3DoF();

      protected:
      private:
    };

    template <class T>
    Planar3DoF<T>::Planar3DoF()  //
      : Manipulator<T, 3>(std::move(SystemSerialization(FilePath("robots/planar/3dof.yaml")).load().cast<T>()), "joint_ee")
    {}

    template <class T>
    Planar3DoF<T>::Planar3DoF(const std::filesystem::path &assets_folder)
      : Manipulator<T, 3>(std::move(SystemSerialization(FilePath(assets_folder / "robots/planar/3dof.yaml")).load().cast<T>()), "joint_ee")
    {}

    template <class T>
    Planar3DoF<T>::~Planar3DoF()
    {}

}  // namespace gafro