#include <deque>
#include <filter/filter.hpp>

namespace movingAverage
{
class movingAverage : public filter::filter
{
public:
  double statistical(const double & number) override
  {
    dq.push_back(number);
    if (4 < dq.size()) {
      sum = sum - dq.front() + number;
      dq.pop_front();
    } else {
      sum = sum + number;
    }
    return sum / dq.size();
  }

protected:
  double sum = 0;
  std::deque<double> dq;
};
}  // namespace movingAverage

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(movingAverage::movingAverage, filter::filter)
