#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//TODO: Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res) {
    ROS_INFO("DriveToTargetRequest Received - linearX: %f ; angularZ: %f", (float)req.linear_x, (float)req.angular_z);



    // Create a motor_command object of type geometry_msgs::Twist
    geometry_msgs::Twist motor_command;
    // Set wheel velocities, forward [0.5, 0.0]
    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;
    // Publish angles to drive the robot
    motor_command_publisher.publish(motor_command);
 
    // reutrn response?
    res.msg_feedback = "Set velocities: linearX: " + std::to_string((float)req.linear_x) + "; angularZ: " + std::to_string((float)req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);
    return true;
}


int main(int argc, char** argv)
{
        // Initialize a ROS node
        ros::init(argc, argv, "drive_bot");

        // Create a ROS NodeHandle object
        ros::NodeHandle n;

        // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
        motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

        // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
        ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
        ROS_INFO("Ready to send velocity commands");

        // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
        // while (ros::ok()) {
        //     // Create a motor_command object of type geometry_msgs::Twist
        //     geometry_msgs::Twist motor_command;
        //     // Set wheel velocities, forward [0.5, 0.0]
        //     motor_command.linear.x = 0.5;
        //     motor_command.angular.z = 0.0;
        //     // Publish angles to drive the robot
        //     motor_command_publisher.publish(motor_command);
        // }

        // TODO: Handle ROS communication events
        ros::spin();

        return 0;
}