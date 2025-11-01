#include <Circuits.h>

#include <iostream>

class MyCircuit : public RootCircuit
{
	NandGate nand;


public:
	MyCircuit()
		: RootCircuit(
			{
				new ConsoleBitInput("IN1"),
				new ConstantBitInput(1)
			}, 
			{
				new ConsoleBitOutput("OUT1")
			}
		)
	{
		connectors = {
			new Connector(inputs[0], 0, &nand, 0),
			new Connector(inputs[1], 0, &nand, 1),
			new Connector(&nand, 0, outputs[0], 0),
		};
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