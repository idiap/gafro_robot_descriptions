#include <gafro_robot_descriptions/SystemVisual.hpp>
#include <gafro_robot_descriptions/serialization/FilePath.hpp>
#include <gafro_robot_descriptions/serialization/SystemSerialization.hpp>
#include <gafro_robot_descriptions/serialization/Visual.hpp>

namespace gafro
{

    SystemVisual::SystemVisual(const std::string &filename) : System<double>(std::move(SystemSerialization(FilePath(filename)).load()))
    {
        visuals_ = SystemSerialization(FilePath(filename)).loadVisuals();
    }

    SystemVisual::~SystemVisual() = default;

    bool SystemVisual::hasVisual(const std::string &link_name) const
    {
        return visuals_.find(link_name) != visuals_.end();
    }

    const Visual *SystemVisual::getVisual(const std::string &link_name) const
    {
        return visuals_.at(link_name).get();
    }

}  // namespace gafro