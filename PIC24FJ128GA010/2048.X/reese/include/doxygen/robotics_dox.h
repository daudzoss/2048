/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 */

/**
 * \page Robotics Robotics Library
 *
 * \section RoboticsLibrary ESOS Robotics Library
 * When developing robots with ESOS, it is easy to divide the robot's
 * functionality into "tasks." Thus is the power of ESOS's ability
 * to directly divide code into tasks. Furthermore, some of the core functionality
 * of a typical robot has been packaged into easily configurable ESOS libraries.
 * Visit the configuration header files below for further details.
 * - servoconfig2.h: Servo Library able to support up to 7 independent servos on a single timer
 * - motorconfig3.h: Motor Library able to support up to 8 independent servos on a single timer
 * - comm_config.h: Comm Library for serial communcation with the PIC, intended for use with Matlab
 *
 * \section RoboticsExamples ESOS Robotics Examples
 * Simple implementations of the \ref RoboticsLibrary "robotics library" have been
 * developed in order to give examples of their use.
 * - esos_servo_example.c: Example of the Servo Library, will rotate a servo over its full range of motion every two seconds
 * - esos_motor_example.c: Example of the Motor Library, will exercise a motor over its possible states (forward, reverse, coast, brake high, and brake low) for three seconds each
 * - esos_comm_example.c: Example of the Comm Library, will respond to well formed packets and echo back incremented values
 *
 */