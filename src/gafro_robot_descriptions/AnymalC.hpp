// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <gafro/robot/Quadruped.hpp>
//
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>
//
#include <filesystem>

namespace gafro
{

    template <class T>
    class AnymalC : public Quadruped<T, 3>
    {
      public:
        AnymalC();

        AnymalC(const std::filesystem::path &assets_folder);

        virtual ~AnymalC();

      protected:
      private:
    };

    template <class T>
    AnymalC<T>::AnymalC()  //
      : Quadruped<T, 3>(std::move(SystemSerialization(FilePath("robots/anymal_c/anymal_c.yaml")).load().cast<T>()),
                        { "LF_shank_fixed_LF_FOOT", "LH_shank_fixed_LH_FOOT", "RF_shank_fixed_RF_FOOT", "RH_shank_fixed_RH_FOOT" })
    {}

    template <class T>
    AnymalC<T>::AnymalC(const std::filesystem::path &assets_folder)
      : Quadruped<T, 3>(std::move(SystemSerialization(FilePath(assets_folder / "robots/anymal_c/anymal_c.yaml")).load().cast<T>()),
                        { "LF_shank_fixed_LF_FOOT", "LH_shank_fixed_LH_FOOT", "RF_shank_fixed_RF_FOOT", "RH_shank_fixed_RH_FOOT" })
    {}

    template <class T>
    AnymalC<T>::~AnymalC()
    {}

}  // namespace gafro