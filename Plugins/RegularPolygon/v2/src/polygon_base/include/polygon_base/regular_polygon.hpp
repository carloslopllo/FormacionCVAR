#ifndef polygon_base_RegularPolygon_HPP
#define polygon_base_RegularPolygon_HPP

namespace polygon_base
{
class RegularPolygon
{
public:
  virtual void initialize(double side_length) = 0;
  virtual double area() = 0;
  virtual ~RegularPolygon() {}

protected:
  RegularPolygon() {}
};
}  // namespace polygon_base

#endif