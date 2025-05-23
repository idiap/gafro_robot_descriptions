// SPDX-FileCopyrightText: Idiap Research Institute <contact@idiap.ch>
//
// SPDX-FileContributor: Tobias Loew <tobias.loew@idiap.ch
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <string>

namespace gafro
{

    class FilePath
    {
      public:
        FilePath(const std::string &path);

        virtual ~FilePath();

        bool exists() const;

        operator std::string() const;

      protected:
      private:
        std::string path_;
    };

}  // namespace gafro