/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#define USE_GAME_SINGLE_STICK_DRIVE_MODE


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  motor_left_0.SetInverted(false);
  motor_left_1.SetInverted(false);
  motor_right_0.SetInverted(true);
  motor_right_1.SetInverted(true);
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

void Robot::TeleopPeriodic() {
  #ifdef USE_TRADITIONAL_TANK_DRIVE_MODE
  /* traditional Tank drive */
  double y_left = -stick_0.GetY(frc::GenericHID::kLeftHand);
  double y_right = -stick_0.GetY(frc::GenericHID::kRightHand);

  y_left *= 0.5;
  y_right *= 0.5;

  double left_motor_output = y_left;
  double right_motor_output = y_right;
  #endif    // USE_TRADITIONAL_TANK_DRIVE_MODE

  #ifdef USE_RC_DRIVE_MODE
  double y = -stick_0.GetY(frc::GenericHID::kLeftHand);
  double z = stick_0.GetX(frc::GenericHID::kRightHand);

  z *= 0.5;

  double left_motor_output = y + z;
  double right_motor_output = y - z;
  #endif    // USE_RC_DRIVE_MODE
  
  #ifdef USE_INVERSE_RC_DRIVE_MODE
  double y = -stick_0.GetY(frc::GenericHID::kRightHand);
  double z = stick_0.GetX(frc::GenericHID::kLeftHand);

  z *= 0.5;

  double left_motor_output = y + z;
  double right_motor_output = y - z;
  #endif    // USE_INVERSE_RC_DRIVE_MODE

  #ifdef USE_SINGLE_STICK_DRIVE_MODE
  double y = -stick_0.GetY(frc::GenericHID::kLeftHand);
  double z = stick_0.GetX(frc::GenericHID::kLeftHand);

  z *= 0.5;

  double left_motor_output = y + z;
  double right_motor_output = y - z;
  #endif    // USE_SINGLE_STICK_DRIVE_MODE

  #ifdef USE_GAME_SINGLE_STICK_DRIVE_MODE
  double y = -stick_0.GetY(frc::GenericHID::kLeftHand);
  double z = stick_0.GetX(frc::GenericHID::kLeftHand);

  z *= 0.5;
  if (y < 0) {
    z *= -1;
  }

  double left_motor_output = y + z;
  double right_motor_output = y - z;
  #endif    // USE_GAME_SINGLE_STICK_DRIVE_MODE

  #ifdef USE_YHC_DRIVE_MODE
  double y = -stick_0.GetY(frc::GenericHID::kLeftHand);
  double z = -stick_0.GetTriggerAxis(frc::GenericHID::kLeftHand) + stick_0.GetTriggerAxis(frc::GenericHID::kRightHand);

  z *= 0.5;

  double left_motor_output = y + z;
  double right_motor_output = y - z;
  #endif    // USE_YHC_DRIVE_MODE
  
  motor_left_0.Set(left_motor_output);
  motor_left_1.Set(left_motor_output);
  motor_right_0.Set(right_motor_output);
  motor_right_1.Set(right_motor_output);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
