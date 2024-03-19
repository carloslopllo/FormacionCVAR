#include <cmath>
#include <polygon_base/regular_polygon.hpp>

namespace triangle
{
class triangle : public polygon_base::RegularPolygon
{
public:
  void initialize(double side_length) override { side_length_ = side_length; }
  double area() override { return 0.5 * side_length_ * getHeight(); }
  double getHeight()
  {
    return sqrt((side_length_ * side_length_) - ((side_length_ / 2) * (side_length_ / 2)));
  }

protected:
  double side_length_;
};
}  // namespace triangle

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(triangle::triangle, polygon_base::RegularPolygon)