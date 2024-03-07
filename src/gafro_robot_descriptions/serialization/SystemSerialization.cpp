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

#include <gafro/robot/FixedJoint.hxx>
#include <gafro/robot/Link.hxx>
#include <gafro/robot/PrismaticJoint.hxx>
#include <gafro/robot/RevoluteJoint.hxx>
#include <gafro/robot/System.hxx>
//
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>
#include <gafro_robot_descriptions/serialization/Visual.hpp>

namespace gafro
{

    SystemSerialization::SystemSerialization(const std::string &filename)  //
      : root_node_(YAML::LoadFile(filename)), root_folder(std::filesystem::path(filename).remove_filename())
    {}

    SystemSerialization::SystemSerialization(const YAML::Node &root_node)  //
      : root_node_(YAML::Clone(root_node))
    {}

    SystemSerialization::~SystemSerialization() = default;

    System<double> SystemSerialization::load()
    {
        return create();
    }

    System<double> SystemSerialization::create()
    {
        System<double> system;

        system.setName(getValue<std::string>(root_node_, { "system", "name" }));

        YAML::Node root = root_node_["system"]["root_link"];

        if (!root)
        {
            throw std::runtime_error("chain has no root link!");
        }

        YAML::Node node = root_node_["links"][root.as<std::string>()];

        addElement(system, node);

        for (std::unique_ptr<gafro::Link<double>> &link : system.getLinks())
        {
            {
                YAML::Node joints = root_node_["links"][link->getName()]["joints"];

                if (joints)
                {
                    for (const std::string &joint_name : joints.as<std::vector<std::string>>())
                    {
                        {
                            const gafro::Joint<double> *joint = system.getJoint(joint_name);

                            if (joint)
                            {
                                link->addChildJoint(joint);
                            }
                        }
                    }
                }
            }

            {
                YAML::Node parent_joint = root_node_["links"][link->getName()]["parent_joint"];

                if (parent_joint)
                {
                    const gafro::Joint<double> *joint = system.getJoint(parent_joint.as<std::string>());

                    if (joint)
                    {
                        link->setParentJoint(joint);
                    }
                }
            }
        }

        for (std::unique_ptr<gafro::Joint<double>> &joint : system.getJoints())
        {
            {
                YAML::Node link_name = root_node_["joints"][joint->getName()]["child_link"];

                if (link_name)
                {
                    const Link<double> *link = system.getLink(link_name.as<std::string>());

                    if (link)
                    {
                        joint->setChildLink(link);
                    }
                }
            }

            {
                YAML::Node link_name = root_node_["joints"][joint->getName()]["parent_link"];

                if (link_name)
                {
                    const Link<double> *link = system.getLink(link_name.as<std::string>());

                    if (link)
                    {
                        joint->setParentLink(link);
                    }
                    else
                    {
                        std::cout << "no link " << link_name.as<std::string>() << std::endl;
                    }
                }
                else
                {
                    std::cout << joint->getName() << " has no parent link!" << std::endl;
                }
            }
        }

        system.finalize();

        return system;
    }

    void SystemSerialization::addElement(System<double> &system, const YAML::Node &node)
    {
        if (!node)
        {
            return;
        }

        addLink(system, node);

        if (!node["joints"])
        {
            return;
        }

        for (const std::string &joint_name : node["joints"].as<std::vector<std::string>>())
        {
            YAML::Node joint = root_node_["joints"][joint_name];

            addJoint(system, joint);

            YAML::Node child_link = root_node_["joints"][joint_name]["child_link"];

            if (child_link)
            {
                addElement(system, root_node_["links"][child_link.as<std::string>()]);
            }
        }
    }

    void SystemSerialization::addLink(System<double> &system, const YAML::Node &node)
    {
        std::unique_ptr<Link<double>> link = std::make_unique<Link<double>>();

        std::string name = getValue<std::string>(node, { "name" });

        link->setName(name);

        if (!node["inertial"])
        {
            throw std::runtime_error("link '" + node["name"].as<std::string>() + "' has no inertial parameters!");
        }

        link->setCenterOfMass(Translator<double>(typename Translator<double>::Generator({
          getValue<double>(node, { "inertial", "origin", "position", "x" }),  //
          getValue<double>(node, { "inertial", "origin", "position", "y" }),  //
          getValue<double>(node, { "inertial", "origin", "position", "z" })   //
        })));

        link->setMass(getValue<double>(node, { "inertial", "mass" }));

        link->setInertia(Inertia<double>(getValue<double>(node, { "inertial", "mass" }),           //
                                         getValue<double>(node, { "inertial", "inertia", "xx" }),  //
                                         getValue<double>(node, { "inertial", "inertia", "xy" }),  //
                                         getValue<double>(node, { "inertial", "inertia", "xz" }),  //
                                         getValue<double>(node, { "inertial", "inertia", "yy" }),  //
                                         getValue<double>(node, { "inertial", "inertia", "yz" }),  //
                                         getValue<double>(node, { "inertial", "inertia", "zz" })));

        system.addLink(std::move(link));
    }

    std::unordered_map<std::string, std::unique_ptr<Visual>> SystemSerialization::loadVisuals()
    {
        std::unordered_map<std::string, std::unique_ptr<Visual>> visuals;

        std::string system_name = getValue<std::string>(root_node_, { "system", "name" });

        for (YAML::const_iterator it = root_node_["links"].begin(); it != root_node_["links"].end(); ++it)
        {
            YAML::Node link_node = it->second;
            std::string name = getValue<std::string>(link_node, { "name" });

            if (link_node["visual"])
            {
                std::string type = getValue<std::string>(link_node, { "visual", "type" });

                Translator<double> translator(typename Translator<double>::Generator({
                  getValue<double>(link_node, { "visual", "origin", "position", "x" }),  //
                  getValue<double>(link_node, { "visual", "origin", "position", "y" }),  //
                  getValue<double>(link_node, { "visual", "origin", "position", "z" })   //
                }));

                Rotor<double> rotor =
                  Rotor<double>::fromQuaternion(Eigen::Quaterniond({ getValue<double>(link_node, { "visual", "origin", "orientation", "w" }),  //
                                                                     getValue<double>(link_node, { "visual", "origin", "orientation", "x" }),  //
                                                                     getValue<double>(link_node, { "visual", "origin", "orientation", "y" }),  //
                                                                     getValue<double>(link_node, { "visual", "origin", "orientation", "z" }) }));

                Motor<double> motor(translator, rotor);

                if (type == "sphere")
                {
                    visuals.emplace(
                      std::make_pair(name, std::make_unique<gafro::visual::Sphere>(getValue<double>(link_node, { "visual", "radius" }), motor)));
                }
                else if (type == "mesh")
                {
                    std::string file = root_folder.empty() ?                                                                                     //
                                         FilePath("robots/" + system_name + "/" + getValue<std::string>(link_node, { "visual", "filename" })) :  //
                                         FilePath((root_folder / getValue<std::string>(link_node, { "visual", "filename" })).string());

                    visuals.emplace(std::make_pair(
                      name, std::make_unique<gafro::visual::Mesh>(
                              root_folder.empty() ?                                                                                     //
                                FilePath("robots/" + system_name + "/" + getValue<std::string>(link_node, { "visual", "filename" })) :  //
                                FilePath((root_folder / getValue<std::string>(link_node, { "visual", "filename" })).string()),          //
                              getValue<double>(link_node, { "visual", "scale", "x" }),                                                  //
                              getValue<double>(link_node, { "visual", "scale", "y" }),                                                  //
                              getValue<double>(link_node, { "visual", "scale", "z" }), motor)));
                }
                else if (type == "cylinder")
                {
                    visuals.emplace(
                      std::make_pair(name, std::make_unique<gafro::visual::Cylinder>(getValue<double>(link_node, { "visual", "length" }),  //
                                                                                     getValue<double>(link_node, { "visual", "radius" }), motor)));
                }
                else if (type == "box")
                {
                    visuals.emplace(
                      std::make_pair(name, std::make_unique<gafro::visual::Box>(getValue<double>(link_node, { "visual", "length" }),  //
                                                                                getValue<double>(link_node, { "visual", "width" }),   //
                                                                                getValue<double>(link_node, { "visual", "height" }), motor)));
                }
            }
        }

        return visuals;
    }

    void SystemSerialization::addJoint(System<double> &system, const YAML::Node &node)
    {
        std::unique_ptr<Joint<double>> joint;

        std::string joint_type = node["type"].as<std::string>();

        if (joint_type == "fixed")
        {
            joint = std::make_unique<FixedJoint<double>>();
        }
        else if (joint_type == "revolute")
        {
            joint = std::make_unique<RevoluteJoint<double>>();

            static_cast<RevoluteJoint<double> *>(joint.get())
              ->setAxis(RevoluteJoint<double>::Axis(Eigen::Vector3d({ getValue<double>(node, { "axis", "x" }),  //
                                                                      getValue<double>(node, { "axis", "y" }),  //
                                                                      getValue<double>(node, { "axis", "z" }) })
                                                      .normalized()));
        }
        else if (joint_type == "prismatic")
        {
            joint = std::make_unique<PrismaticJoint<double>>();

            static_cast<PrismaticJoint<double> *>(joint.get())
              ->setAxis(PrismaticJoint<double>::Axis({ getValue<double>(node, { "axis", "x" }),  //
                                                       getValue<double>(node, { "axis", "y" }),  //
                                                       getValue<double>(node, { "axis", "z" }) }));
        }
        else
        {
            throw std::runtime_error("unknown joint type " + joint_type);
        }

        joint->setName(getValue<std::string>(node, { "name" }));

        Translator<double> t(Translator<double>::Generator({ getValue<double>(node, { "transform", "translation", "x" }),
                                                             getValue<double>(node, { "transform", "translation", "y" }),
                                                             getValue<double>(node, { "transform", "translation", "z" }) }));

        Rotor<double> r = Rotor<double>::fromQuaternion(Eigen::Quaterniond({ getValue<double>(node, { "transform", "rotation", "w" }),  //
                                                                             getValue<double>(node, { "transform", "rotation", "x" }),  //
                                                                             getValue<double>(node, { "transform", "rotation", "y" }),  //
                                                                             getValue<double>(node, { "transform", "rotation", "z" }) }));

        joint->setFrame(Motor<double>(t * r));

        if (joint_type != "fixed")
        {
            joint->setLimits({ getValue<double>(node, { "limits", "lower" }),     //
                               getValue<double>(node, { "limits", "upper" }),     //
                               getValue<double>(node, { "limits", "velocity" }),  //
                               getValue<double>(node, { "limits", "effort" }) });
        }

        system.addJoint(std::move(joint));
    }

}  // namespace gafro