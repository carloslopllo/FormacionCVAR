#include <filter/filter.hpp>

namespace maximum
{
class maximum : public filter::filter
{
public:
  double statistical(const double & number) override
  {
    if (first) {
      maximumCurrent = number;
      first = false;
    } else if (maximumCurrent < number) {
      maximumCurrent = number;
    }
    return maximumCurrent;
  }

protected:
  bool first = true;
  double maximumCurrent = 0;
};
}  // namespace maximum

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(maximum::maximum, filter::filter)
