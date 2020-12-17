/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

/**
 * TeleopPeriodic is executed repeatedly during the Teleop Mode
 * 机器人手动操作模式下会反复调用 TeleopPeriodic 方法
 */
void Robot::TeleopPeriodic() {
  /* Get Xbox axis value | 读取手柄摇杆的数值 */
  double y = -stick_0.GetY(frc::GenericHID::kLeftHand);     // y need to be inverted so that front is +1
  double z = stick_0.GetX(frc::GenericHID::kRightHand);     // z is for rotation

  /* multiply by a factor to decrease speed */
  y *= 0.2;
  z *= 0.2;
  
  /* calculate the expected output value for each side of the motor | 计算每侧电机输出值 */
  double left_motor_output = y + z;
  double right_motor_output = -y + z;

  /* clamp the output value in range [-1, 1] | 将输出值限制在 [-1, 1] 的范围内 */
  left_motor_output = left_motor_output > 1 ? 1 : left_motor_output;
  left_motor_output = left_motor_output < -1 ? -1 : left_motor_output;
  
  right_motor_output = right_motor_output > 1 ? 1 : right_motor_output;
  right_motor_output = right_motor_output < -1 ? -1 : right_motor_output;

  /* set motor output | 将数值传给电机控制器 */
  m_left_0.Set(left_motor_output);
  m_right_0.Set(right_motor_output);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
