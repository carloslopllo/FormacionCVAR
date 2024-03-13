#include <cmath>
#include <polygon_base/regular_polygon.hpp>

namespace square
{
class square : public polygon_base::RegularPolygon
{
public:
  void initialize(double side_length) override { side_length_ = side_length; }
  double area() override { return side_length_ * side_length_; }

protected:
  double side_length_;
};
}  // namespace square

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(square::square, polygon_base::RegularPolygon)