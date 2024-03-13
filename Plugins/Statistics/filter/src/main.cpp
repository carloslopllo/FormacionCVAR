#include <chrono>
#include <filter/filter.hpp>
#include <pluginlib/class_loader.hpp>
#include <thread>

int main(int argc, char ** argv)
{
  (void)argc;
  (void)argv;

  pluginlib::ClassLoader<filter::filter> poly_loader("filter", "filter::filter");

  std::shared_ptr<filter::filter> movingAverage =
    poly_loader.createSharedInstance("movingAverage::movingAverage");
  std::shared_ptr<filter::filter> minimum = poly_loader.createSharedInstance("minimum::minimum");
  std::shared_ptr<filter::filter> maximum = poly_loader.createSharedInstance("maximum::maximum");

  double data = 1.0;
  bool positive = true;
  while (true) {
    try {
      printf("movingAverage: %.2f\n", movingAverage->statistical(data));
      printf("minimum: %.2f\n", minimum->statistical(data));
      printf("maximum: %.2f\n", maximum->statistical(data));
      data = -data;
      if (positive) {
        --data;
      } else {
        ++data;
      }
      positive = !positive;
      std::this_thread::sleep_for(std::chrono::seconds(3));
    } catch (pluginlib::PluginlibException & ex) {
      printf("The plugin failed to load for some reason. Error: %s\n", ex.what());
    }
  }
  return 0;
}
