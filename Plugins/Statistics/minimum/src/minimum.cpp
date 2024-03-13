#include <filter/filter.hpp>

namespace minimum
{
class minimum : public filter::filter
{
public:
  double statistical(const double & number) override
  {
    if (first) {
      minimumCurrent = number;
      first = false;
    } else if (number < minimumCurrent) {
      minimumCurrent = number;
    }
    return minimumCurrent;
  }

protected:
  bool first = true;
  double minimumCurrent = 0;
};
}  // namespace minimum

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(minimum::minimum, filter::filter)
