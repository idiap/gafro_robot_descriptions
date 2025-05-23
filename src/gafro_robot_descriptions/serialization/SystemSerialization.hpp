// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <yaml-cpp/yaml.h>
//
#include <filesystem>
//
#include <gafro/robot/System.hpp>

namespace gafro
{

    // class Visual;

    class SystemSerialization
    {
      public:
        SystemSerialization(const std::string &filename);

        SystemSerialization(const YAML::Node &root_node);

        virtual ~SystemSerialization();

        System<double> load();

        // std::unordered_map<std::string, std::unique_ptr<Visual>> loadVisuals();

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