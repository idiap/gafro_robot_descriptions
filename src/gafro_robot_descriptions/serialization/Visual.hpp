// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <memory>
#include <string>
//
#include <gafro/algebra/cga/Motor.hpp>
#include <gafro/robot/Link.hpp>

namespace gafro::visual
{

    using Visual = gafro::LinkVisual;

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