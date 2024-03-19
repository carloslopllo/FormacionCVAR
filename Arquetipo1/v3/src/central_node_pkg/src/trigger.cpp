#ifndef __trigger_cpp__
#define __trigger_cpp__

#include "central_node_pkg/trigger.hpp"

void trigger1(const inputs & in, outputs & out) { out.sum.data = in.data1.data + in.data2.data; }

void def_trigger(const inputs & in, outputs & out)
{
  out.minus.data = in.data1.data - in.data2.data;
}

#endif
