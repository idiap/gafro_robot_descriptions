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

#include <memory>
#include <string>
//
#include <gafro/algebra/Motor.hpp>

namespace gafro
{
    class Visual
    {
      public:
        enum class Type
        {
            SPHERE,
            MESH,
            CYLINDER,
            BOX
        };

        Visual(const Type &type, const Motor<double> &transform);

        virtual ~Visual() = default;

        virtual std::unique_ptr<Visual> copy() const = 0;

        const Type &getType() const;

        const Motor<double> &getTransform() const;

      private:
        const Type type_;

        Motor<double> transform_;
    };
}  // namespace gafro

namespace gafro::visual
{

    class Sphere : public Visual
    {
      public:
        Sphere(const double &radius, const Motor<double> &transform = Motor<double>());

        ~Sphere() = default;

        std::unique_ptr<Visual> copy() const;

        const double &getRadius() const;

      private:
        double radius_;
    };

    class Mesh : public Visual
    {
      public:
        Mesh(const std::string &filename, const double &scale_x, const double &scale_y, const double &scale_z,
             const Motor<double> &transform = Motor<double>());

        ~Mesh() = default;

        std::unique_ptr<Visual> copy() const;

        const std::string &getFilename() const;

        const double &getScaleX() const;

        const double &getScaleY() const;

        const double &getScaleZ() const;

      private:
        std::string filename_;
        double scale_x_;
        double scale_y_;
        double scale_z_;
    };

    class Cylinder : public Visual
    {
      public:
        Cylinder(const double &length, const double &radius, const Motor<double> &transform = Motor<double>());

        ~Cylinder() = default;

        std::unique_ptr<Visual> copy() const;

        const double &getLength() const;

        const double &getRadius() const;

      private:
        double length_;
        double radius_;
    };

    class Box : public Visual
    {
      public:
        Box(const double &dim_x, const double &dim_y, const double &dim_z, const Motor<double> &transform = Motor<double>());

        ~Box() = default;

        std::unique_ptr<Visual> copy() const;

        const double &getDimX() const;

        const double &getDimY() const;

        const double &getDimZ() const;

      private:
        double dim_x_;
        double dim_y_;
        double dim_z_;
    };
}  // namespace gafro::visual