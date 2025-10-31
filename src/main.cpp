#include <iostream>
#include <Circuits.h>


int main()
{
	ConsoleBitInput in1("IN1");
	ConstantBitInput in2(1);
	ConsoleBitOutput out1("OUT1");
	NandGate nand;
	Connector c1(&in1, 0, &nand, 0);
	Connector c2(&in2, 0, &nand, 1);
	Connector c3(&nand, 0, &out1, 0);

	Circuit circuit({ &in1, &in2 }, { &out1 });
	circuit.Update();

	//TODO: rewrite update sequence building algorithm to perform a normal topological sort

	return 0;
}