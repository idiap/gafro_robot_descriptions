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

#include <yaml-cpp/yaml.h>
//
#include <filesystem>
//
#include <gafro/robot/System.hpp>

namespace gafro
{

    class Visual;

    class SystemSerialization
    {
      public:
        SystemSerialization(const std::string &filename);

        SystemSerialization(const YAML::Node &root_node);

        virtual ~SystemSerialization();

        System<double> load();

        std::unordered_map<std::string, std::unique_ptr<Visual>> loadVisuals();

      private:
        System<double> create();

        void addElement(System<double> &system, const YAML::Node &node);

        void addLink(System<double> &system, const YAML::Node &node);

        void addJoint(System<double> &system, const YAML::Node &node);

        template <class T>
        T getValue(const YAML::Node &root, const std::vector<std::string> &keys)
        {
            YAML::Node node = YAML::Clone(root);

            std::string path = "";

            for (const std::string &key : keys)
            {
                node = node[key];

                path += "/" + key;

                if (!node)
                {
                    throw std::runtime_error(path + " doesn't exist!");
                }
            }

            return node.as<T>();
        }

      protected:
      private:
        const YAML::Node root_node_;
        const std::filesystem::path root_folder;
    };

}  // namespace gafro