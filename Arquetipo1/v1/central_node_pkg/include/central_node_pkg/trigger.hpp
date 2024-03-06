#ifndef __trigger_hpp__
#define __trigger_hpp__

struct inputs {
	int input1, input2;
};

struct outputs {
	int output1, output2;
};

void trigger (const inputs &, outputs &);

#endif
