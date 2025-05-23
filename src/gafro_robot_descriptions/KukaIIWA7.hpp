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
    class KukaIIWA7 : public Manipulator<T, 7>
    {
      public:
        KukaIIWA7();

        KukaIIWA7(const std::filesystem::path &assets_folder);

        virtual ~KukaIIWA7();

      protected:
      private:
    };

    template <class T>
    KukaIIWA7<T>::KukaIIWA7()  //
      : Manipulator<T, 7>(std::move(SystemSerialization(FilePath("robots/kuka/iiwa7/iiwa7.yaml")).load().cast<T>()), "iiwa_joint_ee")
    {}

    template <class T>
    KukaIIWA7<T>::KukaIIWA7(const std::filesystem::path &assets_folder)
      : Manipulator<T, 7>(std::move(SystemSerialization(FilePath(assets_folder / "robots/kuka/iiwa7/iiwa7.yaml")).load().cast<T>()), "iiwa_joint_ee")
    {}

    template <class T>
    KukaIIWA7<T>::~KukaIIWA7()
    {}

}  // namespace gafro