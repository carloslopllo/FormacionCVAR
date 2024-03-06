#ifndef __trigger_cpp__
#define __trigger_cpp__

#include "../include/central_node_pkg/trigger.hpp"

void trigger (const inputs & in, outputs & out) {
	out.output1 = in.input1 + in.input2;

	out.output2 = in.input1 - in.input2;
}

#endif
