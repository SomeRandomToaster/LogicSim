#include <Circuits.h>

#include <iostream>

class MyCircuit : public RootCircuit
{
	ConsoleBitInput in1;
	ConstantBitInput in2;
	ConsoleBitOutput out1;
	NandGate nand;
	Connector c1, c2, c3;


public:
	MyCircuit()
		:	RootCircuit({ &in1, &in2 }, { &out1 }),
			
			in1("IN1"),
			in2(1),
			out1("OUT1"),
			
			c1(&in1, 0, &nand, 0),
			c2(&in2, 0, &nand, 1),
			c3(&nand, 0, &out1, 0)
	{
		Init();
	}
};


int main()
{
	

	MyCircuit circuit;
	circuit.Update();

	//TODO: rewrite update sequence building algorithm to perform a normal topological sort

	return 0;
}