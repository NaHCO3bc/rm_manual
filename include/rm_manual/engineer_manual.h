//
// Created by qiayuan on 5/23/21.
//

#ifndef RM_MANUAL_ENGINEER_MANUAL_H_
#define RM_MANUAL_ENGINEER_MANUAL_H_
#include "rm_manual/chassis_gimbal_manual.h"

#include <std_srvs/Empty.h>
#include <actionlib/client/simple_action_client.h>
#include <rm_common/decision/calibration_queue.h>
#include <std_msgs/Float64.h>
#include <rm_msgs/EngineerAction.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <utility>

namespace rm_manual
{
class EngineerManual : public ChassisGimbalManual
{
public:
  explicit EngineerManual(ros::NodeHandle& nh);
  void run() override;

private:
  void checkKeyboard() override;
  void updateRc() override;
  void updatePc() override;
  void sendCommand(const ros::Time& time) override;
  void drawUi(const ros::Time& time) override;
  void remoteControlTurnOff() override;
  void chassisOutputOn() override;
  void rightSwitchDownRise() override;
  void rightSwitchMidRise() override;
  void rightSwitchUpRise() override;
  void leftSwitchUpRise() override;
  void leftSwitchUpFall();
  void leftSwitchDownFall();
  void runStepQueue(const std::string& step_queue_name);
  void actionActiveCallback()
  {
    operating_mode_ = MIDDLEWARE;
  }
  void updateServo();
  void actionFeedbackCallback(const rm_msgs::EngineerFeedbackConstPtr& feedback);
  void actionDoneCallback(const actionlib::SimpleClientGoalState& state, const rm_msgs::EngineerResultConstPtr& result);
  void ctrlQPress();     // choose "left_" situation // "has_stone_"
  void ctrlWPress();     // choose "mid_" situation // "no_stone_"
  void ctrlEPress();     // choose "right_" situation
  void ctrlAPress();     // choose "sky" situation
  void ctrlSPress();     // choose "grasp" situation
  void ctrlDPress();     // choose "exchange" situation
  void ctrlZPress();     // choose "store" situation
  void ctrlXPress();     // choose "_gain" situation
  void ctrlCPress();     // cancel and delete scence
  void ctrlVPress();     // choose "small_island" situation
  void ctrlBPress();     // choose "ground_stone" situation
  void ctrlFPress();     // execute next
  void ctrlGPress();     // execute repeat
  void ctrlRPress();     // calibration
  void shiftPressing();  // low speed
  void shiftRelease();   // low speed
  void shiftQPress();    // servo's angular z
  void shiftQRelease();  // servo's angular z
  void shiftEPress();    // servo's angular z
  void shiftERelease();  // servo's angular z
  void ZPress();         // card long
  void XPress();         // card short
  void CPress();         // drag
  void BPress();         // back home
  void VPress();         // change mode servo
  void GPress();         // gripper
  void GRelease();       // gripper
  void JudgePrefix();
  void JudgeRoot();
  enum
  {
    MANUAL,
    MIDDLEWARE
  };
  enum
  {
    SERVO,
    JOINT
  };

  double angular_z_scale_;
  std::string prefix_, root_;
  int prefix_num_{}, root_num_{};
  int operating_mode_, servo_mode_;
  actionlib::SimpleActionClient<rm_msgs::EngineerAction> action_client_;
  rm_common::CalibrationQueue *power_on_calibration_{}, *arm_calibration_{};
  rm_common::JointPositionBinaryCommandSender* drag_command_sender_;
  rm_common::CardCommandSender* card_command_sender_;
  rm_common::Vel3DCommandSender* servo_command_sender_;
  InputEvent left_switch_up_event_, left_switch_down_event_, ctrl_q_event_, ctrl_a_event_, ctrl_z_event_, ctrl_w_event_,
      ctrl_s_event_, ctrl_x_event_, ctrl_e_event_, ctrl_d_event_, ctrl_c_event_, ctrl_b_event_, ctrl_v_event_, z_event_,
      x_event_, c_event_, v_event_, b_event_, shift_z_event_, shift_x_event_, shift_c_event_, shift_v_event_,
      shift_b_event_, ctrl_r_event_, shift_q_event_, shift_e_event_, ctrl_g_event_, shift_r_event_, ctrl_f_event_,
      shift_event_, g_event_;
};

}  // namespace rm_manual
#endif  // RM_MANUAL_ENGINEER_MANUAL_H_
