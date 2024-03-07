#pragma once

#include <gafro/robot/System.hxx>

namespace gafro
{
    class Visual;

    class SystemVisual : public System<double>
    {
      public:
        SystemVisual(const std::string &filename);

        virtual ~SystemVisual();

        bool hasVisual(const std::string &link_name) const;

        const Visual *getVisual(const std::string &link_name) const;

      protected:
      private:
        std::unordered_map<std::string, std::unique_ptr<Visual>> visuals_;
    };

}  // namespace gafro