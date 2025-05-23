// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#include <filesystem>
#include <iostream>
#include <vector>
//
#include <gafro_robot_descriptions/gafro_robot_descriptions_package_config.hpp>
//
#include <gafro_robot_descriptions/serialization/FilePath.hpp>

namespace gafro
{

    FilePath::FilePath(const std::string &path)
    {
        std::filesystem::path filepath(path);

        if (filepath.is_absolute())
        {
            if (std::filesystem::exists(filepath))
            {
                path_ = path;
            }
        }
        else if (filepath.is_relative())
        {
            std::string error_message = "file " + filepath.string() + " not found! checked:";

            std::vector<std::filesystem::path> paths = { filepath,
                                                         "assets" / filepath,                                                   //
                                                         std::filesystem::current_path() / "assets" / filepath,                 //
                                                         std::filesystem::path(GAFRO_ROBOT_DESCRIPTIONS_DIRECTORY) / filepath,  //
                                                         std::filesystem::path("~/gafro/assets") / filepath,                    //
                                                         std::filesystem::path("~/.gafro/assets") / filepath,                   //
                                                         std::filesystem::path("~/.local/gafro/assets") / filepath };

            for (const std::filesystem::path &file : paths)
            {
                if (std::filesystem::exists(file))
                {
                    path_ = file.string();

                    return;
                }

                error_message += "\n\t" + file.string();
            }

            throw std::runtime_error(error_message);
        }
    }

    FilePath::~FilePath() = default;

    bool FilePath::exists() const
    {
        return std::filesystem::exists(path_);
    }

    FilePath::operator std::string() const
    {
        return path_;
    }

}  // namespace gafro