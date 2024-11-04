/*
    Copyright (c) 2022 Idiap Research Institute, http://www.idiap.ch/
    Written by Tobias Löw <https://tobiloew.ch>

    This file is part of gafro.

    gafro is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as
    published by the Free Software Foundation.

    gafro is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gafro. If not, see <http://www.gnu.org/licenses/>.
*/

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
    class LeapHand : public Hand<T, 4, 4>
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
      : Hand<T, 4, 4>(std::move(SystemSerialization(FilePath("robots/leap_hand/leap_hand.yaml")).load().cast<T>()),
                      { "fingertip_center_joint", "fingertip_2_center_joint", "fingertip_3_center_joint", "thumb_center_joint" })
    {}

    template <class T>
    LeapHand<T>::LeapHand(const std::filesystem::path &assets_folder)
      : Hand<T, 4, 4>(std::move(SystemSerialization(FilePath(assets_folder / "robots/leap_hand/leap_hand.yaml")).load().cast<T>()),
                      { "fingertip_center_joint", "fingertip_2_center_joint", "fingertip_3_center_joint", "thumb_center_joint" })
    {}

    template <class T>
    LeapHand<T>::~LeapHand()
    {}

}  // namespace gafro