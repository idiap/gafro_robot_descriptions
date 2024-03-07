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