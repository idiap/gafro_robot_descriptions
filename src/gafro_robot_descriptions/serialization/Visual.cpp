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

#include <gafro/algebra.hpp>
#include <gafro_robot_descriptions/serialization/Visual.hpp>

namespace gafro
{

    Visual::Visual(const Type &type, const Motor<double> &transform) : type_(type), transform_(transform) {}

    const Visual::Type &Visual::getType() const
    {
        return type_;
    }

    const Motor<double> &Visual::getTransform() const
    {
        return transform_;
    }

}  // namespace gafro

namespace gafro::visual
{

    Sphere::Sphere(const double &radius, const Motor<double> &transform) : Visual(Visual::Type::SPHERE, transform), radius_(radius) {}

    std::unique_ptr<Visual> Sphere::copy() const
    {
        return std::make_unique<Sphere>(radius_, getTransform());
    }

    const double &Sphere::getRadius() const
    {
        return radius_;
    }

    Mesh::Mesh(const std::string &filename, const double &scale_x, const double &scale_y, const double &scale_z, const Motor<double> &transform)
      : Visual(Visual::Type::MESH, transform), filename_(filename), scale_x_(scale_x), scale_y_(scale_y), scale_z_(scale_z)
    {}

    std::unique_ptr<Visual> Mesh::copy() const
    {
        return std::make_unique<Mesh>(filename_, scale_x_, scale_y_, scale_z_, getTransform());
    }

    const std::string &Mesh::getFilename() const
    {
        return filename_;
    }

    const double &Mesh::getScaleX() const
    {
        return scale_x_;
    }

    const double &Mesh::getScaleY() const
    {
        return scale_y_;
    }

    const double &Mesh::getScaleZ() const
    {
        return scale_z_;
    }

    Cylinder::Cylinder(const double &length, const double &radius, const Motor<double> &transform)
      : Visual(Visual::Type::CYLINDER, transform), length_(length), radius_(radius)
    {}

    std::unique_ptr<Visual> Cylinder::copy() const
    {
        return std::make_unique<Cylinder>(length_, radius_, getTransform());
    }

    const double &Cylinder::getLength() const
    {
        return length_;
    }

    const double &Cylinder::getRadius() const
    {
        return radius_;
    }

    Box::Box(const double &dim_x, const double &dim_y, const double &dim_z, const Motor<double> &transform)
      : Visual(Visual::Type::BOX, transform), dim_x_(dim_x), dim_y_(dim_y), dim_z_(dim_z)
    {}

    std::unique_ptr<Visual> Box::copy() const
    {
        return std::make_unique<Box>(dim_x_, dim_y_, dim_z_, getTransform());
    }

    const double &Box::getDimX() const
    {
        return dim_x_;
    }

    const double &Box::getDimY() const
    {
        return dim_y_;
    }

    const double &Box::getDimZ() const
    {
        return dim_z_;
    }

}  // namespace gafro::visual