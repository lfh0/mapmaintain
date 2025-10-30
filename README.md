# Install and start：

## Environment：

```bash
sudo apt-get install libompl-dev
sudo apt-get install ros-noetic-octomap-server
sudo apt-get install ros-noetic-map-server
sudo apt-get install ros-noetic-map-msgs
```

## Catkin_make：

```bash
cd AstroimeProjects/park_navigation
catkin_make
source devel/setup.bash / source devel/setup.zsh  #基于终端选择
```

## Start:

### 导航地图生成：

```bash
roslaunch navi_map octomap_convert.launch
rosrun map_server map_saver map:=/projected_map -f /home/kermit/bag
#map:/<ros topic>   -f <path_to_save>
rosrun navi_map read_pcd
#在readPCD.cpp中可以修改读取点云的目录
```

### 生成任务点：

```bash
roslaunch navi_map mapMaintain.launch    #打开地图
rosrun missionmaker missionmaker    #打开记录
#在rviz中用nav_goal按顺序标记任务点，记录在AstroimeProjects/park_navigation/src/mission_maker/roadpoint中

```

### 导航：

```bash
roslaunch navi_map mapMaintain.launch    #打开地图
roslaunch acman_navigation trak_server.launch    #打开跟踪器
roslaunch yhs_can_control yhs_can_control.launch    #实车打开底盘控制
roslaunch car_planner car.launch    #打开车辆路径规划，修改()
rosrun missionmaker pathmaker    #发布路径

```
