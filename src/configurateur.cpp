#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "geometry_msgs/Pose2D.h"

using namespace geometry_msgs; 

int main(int argc, char **argv)
{
    // Initialiser le n�ud
    ros::init(argc, argv, "configurateur");
    ros::NodeHandle nh;

    // R�cup�rer les param�tres avec valeurs par d�faut
    int biais_roue_gauche_marche_avant;
    int biais_roue_gauche_marche_arriere;
    int biais_roue_droite_marche_avant;
    int biais_roue_droite_marche_arriere;
    
    
    // Param�tre obligatoire (pas de valeur par d�faut)
   /* if( (!nh.getParam("biais_roue_gauche_marche_avant", biais_roue_gauche_marche_avant)) ||
     (!nh.getParam("biais_roue_gauche_marche_arriere", biais_roue_gauche_marche_arriere)) ||
    (!nh.getParam("biais_roue_droite_marche_avant", biais_roue_droite_marche_avant))||
    (!nh.getParam("biais_roue_droite_marche_arriere", biais_roue_droite_marche_arriere)))
    {
        ROS_ERROR("Failed to get param 'topic_name'");
        return 1;
    }*/
    
    
    // Param�tres optionnels (avec valeurs par d�faut)
    //nh.param<double>("publish_rate", publish_rate, 1.0); // 1 Hz par d�faut
    
    /*nh.param<double>("biais_roue_gauche_marche_avant", biais_roue_gauche_marche_avant, 1.0); // 0 par d�faut
    nh.param<double>("biais_roue_gauche_marche_arriere", biais_roue_gauche_marche_arriere, 1.0); // 0 par d�faut
    nh.param<double>("biais_roue_droite_marche_avant", biais_roue_droite_marche_avant, 1.0); // 0 par d�faut
    nh.param<double>("biais_roue_droite_marche_arriere", biais_roue_droite_marche_arriere, 1.0); // 0 par d�faut
    */
              
    nh.getParam("biais_roue_gauche_marche_avant", biais_roue_gauche_marche_avant);
    nh.getParam("biais_roue_gauche_marche_arriere", biais_roue_gauche_marche_arriere);
    nh.getParam("biais_roue_droite_marche_avant", biais_roue_droite_marche_avant);
    nh.getParam("biais_roue_droite_marche_arriere", biais_roue_droite_marche_arriere);
                                                   
    
    // Cr�er le publisher
    ros::Publisher setCalG_pub = nh.advertise<geometry_msgs::Pose2D>("/set_calibrationG", 1000);
    ros::Publisher setCalD_pub = nh.advertise<geometry_msgs::Pose2D>("/set_calibrationD", 1000);
    
    
    ros::Duration(1).sleep();
    Pose2D biais_roue_gauche, biais_roue_droite; 
    
    
    biais_roue_gauche.x = biais_roue_gauche_marche_avant;
    biais_roue_gauche.y = biais_roue_gauche_marche_arriere;
    
    
    
    biais_roue_droite.x = biais_roue_droite_marche_avant;
    biais_roue_droite.y = biais_roue_droite_marche_arriere;
    
    
    setCalG_pub.publish(biais_roue_gauche);
    
    setCalD_pub.publish(biais_roue_droite);
    
    ROS_INFO("SUCESS : Biais to parallax : G(%d,%d) ** D(%d,%d)  ",biais_roue_gauche_marche_avant, biais_roue_gauche_marche_arriere,
                                                          biais_roue_droite_marche_avant, biais_roue_droite_marche_arriere);
 
    ros::spin();
    return 0;
}