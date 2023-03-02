#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"

#include "geometry_msgs/msg/twist.hpp"



void turnTurtle(rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub, float linear, float angular)
{
    geometry_msgs::msg::Twist twist;
    twist.linear.x = linear;
    twist.angular.z = angular;

    for (int i = 0; i < 3; i++)
    {
        twist_pub->publish(twist);
        sleep(0.25);
    }
    sleep(2);
    twist.angular.z = 0;
    twist_pub->publish(twist);
}
void moveStraight(rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub, int dist)
{
    geometry_msgs::msg::Twist twist;
    int curr_dist = 0;
    twist.linear.x = 0.5;
    twist.angular.z = 0.0;
    while(curr_dist<=dist){
        twist_pub->publish(twist);
        curr_dist++;
        sleep(1.0);
    }
    sleep(1.0);
}
void makeCircle(rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub, int dist)
{
    geometry_msgs::msg::Twist twist;
    int curr_dist = 0;
    twist.linear.x = 1;
    twist.angular.z = -1.0;
    while(curr_dist<=dist){
        twist_pub->publish(twist);
        curr_dist++;
        sleep(1.0);
    }
}

void drawLetterR(rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_turtle1)
{
    turnTurtle(cmd_vel_turtle1, 0.0, 1.55);
    moveStraight(cmd_vel_turtle1, 5);
    makeCircle(cmd_vel_turtle1, 4);
    turnTurtle(cmd_vel_turtle1, 0.0, 2.35);
    moveStraight(cmd_vel_turtle1, 4);
}

void drawLetterO(rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_turtle2)
{
    //turnTurtle(cmd_vel_turtle2, 0.0, 1.57);
    moveStraight(cmd_vel_turtle2, 6);
    makeCircle(cmd_vel_turtle2, 2);
    turnTurtle(cmd_vel_turtle2, 0.0, -0.15);
    moveStraight(cmd_vel_turtle2, 4);
    makeCircle(cmd_vel_turtle2, 2);
    //moveStraight(cmd_vel_turtle2, 2);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    //rclcpp::spin(std::make_shared<FramePublisher>());
    auto node = rclcpp::Node::make_shared("initials");
    auto cmd_vel_turtle1 = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    auto cmd_vel_turtle2 = node->create_publisher<geometry_msgs::msg::Twist>("/turtle2/cmd_vel", 10);

    drawLetterO(cmd_vel_turtle2);
    drawLetterR(cmd_vel_turtle1);

    rclcpp::shutdown();
    return 0;
}
