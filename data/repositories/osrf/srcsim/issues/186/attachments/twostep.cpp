#include <ros/ros.h>
#include <ros/subscribe_options.h>
#include <sstream>
#include <stdio.h>
#include <termio.h>
#include <ihmc_msgs/FootstepStatusRosMessage.h>
#include <ihmc_msgs/FootstepDataListRosMessage.h>
#include <ihmc_msgs/FootstepDataRosMessage.h>



int main(int argc, char **argv)
{
    ros::init(argc, argv, "twostep");
    ros::NodeHandle n;

    usleep(200000);

    ros::Publisher pub_steps = n.advertise<ihmc_msgs::FootstepDataListRosMessage>("/ihmc_ros/valkyrie/control/footstep_list", 1);

    ros::spinOnce();
    usleep(200000);
    ros::spinOnce();
    usleep(200000);
    ros::spinOnce();

    // left = 0, right = 1
    ihmc_msgs::FootstepDataListRosMessage msg;
    msg.default_transfer_time = 1.5;
    msg.default_swing_time = 1.5;
    msg.execution_mode = 0;
    msg.unique_id = -1;
    
    ihmc_msgs::FootstepDataRosMessage one_step;
    one_step.origin = ihmc_msgs::FootstepDataRosMessage::AT_ANKLE_FRAME;
    one_step.robot_side = ihmc_msgs::FootstepDataRosMessage::LEFT;
    one_step.location.x = -0.15;
    one_step.location.y = 0.1;
    one_step.location.z = 0.07;
    one_step.orientation.x = 0.0;
    one_step.orientation.y = 0.0;
    one_step.orientation.z = 0.919;
    one_step.orientation.w = 0.395;
    one_step.trajectory_type = ihmc_msgs::FootstepDataRosMessage::DEFAULT;
    msg.footstep_data_list.push_back(one_step);
    
    one_step.robot_side = ihmc_msgs::FootstepDataRosMessage::RIGHT;
    one_step.location.x = 0.04;
    one_step.location.y = 0.29;
    one_step.orientation.x = 0.0;
    one_step.orientation.y = 0.0;
    one_step.orientation.z = 0.924;
    one_step.orientation.w = 0.383;
    msg.footstep_data_list.push_back(one_step);


    one_step.robot_side = ihmc_msgs::FootstepDataRosMessage::LEFT;
    one_step.location.x = -0.14;
    one_step.location.y = 0.12;
    one_step.orientation.x = 0.0;
    one_step.orientation.y = 0.0;
    one_step.orientation.z = 0.922;
    one_step.orientation.w = 0.387;
    msg.footstep_data_list.push_back(one_step);
    
    pub_steps.publish(msg);


    ros::spinOnce();
    usleep(200000);
    ros::spinOnce();
    usleep(200000);
    ros::spinOnce();
    usleep(200000);
    ros::spinOnce();
    usleep(200000);
    ros::spinOnce();

    return 0;
}

