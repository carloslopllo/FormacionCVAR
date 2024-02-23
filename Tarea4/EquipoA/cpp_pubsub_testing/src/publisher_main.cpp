#include <fstream>
#include <iostream>
#include <vector>
#include "nodes/publisher.hpp"


int main(int argc, char * argv[])
{
  
if(argc != 2)
  {
    std::cerr << "Error en el numero de argumentos" << std::endl;
    return 1;
  }

  //Abrimos el archivo
  std::ifstream ptr(argv[1]);

  std::vector<double> read_vector = readDouble(ptr);

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>(read_vector));
  rclcpp::shutdown();
  return 0;
}