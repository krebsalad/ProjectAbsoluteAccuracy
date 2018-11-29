
"use strict";

let StopMotion = require('./StopMotion.js')
let CmdJointTrajectory = require('./CmdJointTrajectory.js')
let GetRobotInfo = require('./GetRobotInfo.js')
let StartMotion = require('./StartMotion.js')
let SetDrivePower = require('./SetDrivePower.js')
let SetRemoteLoggerLevel = require('./SetRemoteLoggerLevel.js')

module.exports = {
  StopMotion: StopMotion,
  CmdJointTrajectory: CmdJointTrajectory,
  GetRobotInfo: GetRobotInfo,
  StartMotion: StartMotion,
  SetDrivePower: SetDrivePower,
  SetRemoteLoggerLevel: SetRemoteLoggerLevel,
};
