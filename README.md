# RobotController
RobotController
Copyright (C) 20018 - 2019 by XieMingyou. All rights reserved.

这是本人自主开发的机器人控制程序，本人保留版权。

程序功能简介：  
实现机器人参数配置与管理：基于Qt开发了RobotStudio软件，通过TinyXML保存和加载机器人参数配置；
实现与示教器的数据传输：采用protobuf将机器人的状态和控制变量序列化，采用zlib将变量和程序文件夹压缩解压，通过socket实现TCP传输；
实现机器人算法与控制功能研究：包括运动规划、机器人正逆解等算法，支持机器人参数设置、离线编程、在线示教、状态检测等20余项功能，根据机器人的状态和控制变量进行逻辑判断，实时控制机器人的运动；
实现多线程并发：主线程与数据传输线程、机器人控制线程、状态读取线程、程序编译线程协同运行。

打开RobotController程序：
RobotController.sln

打开RobotStudio程序：
RobotStudio\RobotStudio\RobotStudio.pro
