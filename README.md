## 1 导航地图生成
`roslaunch navi_map octomap_convert.launch`





## 待完成任务：
### 1 地面提取：是否需要提取出地面，或是在slam的流程中将z轴矫正，因为在slam中的odom是相对于起始点的，但是若我投影到地面上，会导致odom的偏移，但若不投影是否误差也会存在，只是投影的倾斜会让障碍物变大