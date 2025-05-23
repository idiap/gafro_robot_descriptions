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
    class KukaIIWA14 : public Manipulator<T, 7>
    {
      public:
        KukaIIWA14();

        KukaIIWA14(const std::filesystem::path &assets_folder);

        virtual ~KukaIIWA14();

      protected:
      private:
    };

    template <class T>
    KukaIIWA14<T>::KukaIIWA14()  //
      : Manipulator<T, 7>(std::move(SystemSerialization(FilePath("robots/kuka/iiwa14/iiwa14.yaml")).load().cast<T>()), "lbr_joint_ee")
    {}

    template <class T>
    KukaIIWA14<T>::KukaIIWA14(const std::filesystem::path &assets_folder)
      : Manipulator<T, 7>(std::move(SystemSerialization(FilePath(assets_folder / "robots/kuka/iiwa14/iiwa14.yaml")).load().cast<T>()), "lbr_joint_ee")
    {}

    template <class T>
    KukaIIWA14<T>::~KukaIIWA14()
    {}

}  // namespace gafro