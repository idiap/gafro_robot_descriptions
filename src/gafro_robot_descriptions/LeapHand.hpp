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
    class LeapHand : public Hand<T, 4, 4, 4, 4>
    {
      public:
        LeapHand();

        LeapHand(const std::filesystem::path &assets_folder);

        virtual ~LeapHand();

      protected:
      private:
    };

    template <class T>
    LeapHand<T>::LeapHand()  //
      : Hand<T, 4, 4, 4, 4>(std::move(SystemSerialization(FilePath("robots/leap_hand/leap_hand.yaml")).load().cast<T>()),
                            { "fingertip_center_joint", "fingertip_2_center_joint", "fingertip_3_center_joint", "thumb_center_joint" })
    {}

    template <class T>
    LeapHand<T>::LeapHand(const std::filesystem::path &assets_folder)
      : Hand<T, 4, 4, 4, 4>(std::move(SystemSerialization(FilePath(assets_folder / "robots/leap_hand/leap_hand.yaml")).load().cast<T>()),
                            { "fingertip_center_joint", "fingertip_2_center_joint", "fingertip_3_center_joint", "thumb_center_joint" })
    {}

    template <class T>
    LeapHand<T>::~LeapHand()
    {}

}  // namespace gafro