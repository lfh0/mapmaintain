#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include <pcl/filters/voxel_grid.h>
#include<pcl_conversions/pcl_conversions.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include<sensor_msgs/PointCloud2.h>
#include<pcl/io/pcd_io.h>//which contains the required definitions to load and store point clouds to PCD and other file formats.
 
int main (int argc, char **argv)
{
  ros::init (argc, argv, "UandBdetect");
  ros::NodeHandle nh;
  std::string pcd_file_path;
  nh.getParam("lab/pcd_file_path", pcd_file_path);

  ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output", 1);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_input(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ> cloud_output;

  sensor_msgs::PointCloud2 output;

  pcl::io::loadPCDFile (pcd_file_path, *cloud_input); //修改自己pcd文件所在路径
  // 滤波操作，将点云中的雷达噪声点过滤一遍
  // pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
  // voxel_grid.setInputCloud(cloud_input);
  // voxel_grid.setLeafSize(0.1, 0.1, 0.1);
  // voxel_grid.filter(cloud_output);
  
  // 滤波操作，将点云中的雷达噪声点过滤一遍
  pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
  sor.setInputCloud(cloud_input);
  sor.setMeanK(20);
  sor.setStddevMulThresh(1.0);
  sor.filter(cloud_output);
  
  //Convert the cloud to ROS message
  pcl::toROSMsg(cloud_output, output);
  output.header.frame_id = "odom";

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    pcl_pub.publish(output);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
