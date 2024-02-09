#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "my_pkgs/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
    AddressBookPublisher() : Node("address_book_publisher")
    {
        address_book_publisher_ = this->create_publisher<my_pkgs::msg::AddressBook>("address_book", 10);

        auto publish_msg = [this]() -> void {

            auto message = my_pkgs::msg::AddressBook();
            message.first_name = "John";
            message.last_name = "Doe";
            message.phone_number = "1-800-555-5555";
            message.phone_type = message.PHONE_TYPE_MOBILE;

            std::cout << "Publishing Contact\nFirst:" << message.first_name << "   Last:" << message.last_name << std::endl;

            this->address_book_publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(1s, publish_msg);
    }

private:
    rclcpp::Publisher<my_pkgs::msg::AddressBook>::SharedPtr address_book_publisher_; // Fixed the message type here
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddressBookPublisher>());
    rclcpp::shutdown();

    return 0;
}

