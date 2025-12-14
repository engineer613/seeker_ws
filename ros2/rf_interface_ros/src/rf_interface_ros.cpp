#include <rclcpp/rclcpp.hpp>
#include "RFInterface.hpp"

class RFInterfaceNode : public rclcpp::Node
{
public:
  RFInterfaceNode() : Node("rf_interface_node")
  {
    RCLCPP_INFO(this->get_logger(), "RF Interface Node started");
  }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RFInterfaceNode>());
  rclcpp::shutdown();
  return 0;
}
