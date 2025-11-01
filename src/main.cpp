#include <Circuits.h>

#include <iostream>

class MyCircuit : public RootCircuit
{
	XorGate xor0;
	AndGate and0;


public:
	MyCircuit()
		: RootCircuit(
			{
				new ConsoleBitInput("IN1"),
				new ConsoleBitInput("IN2")
			}, 
			{
				new ConsoleBitOutput("SUM"),
				new ConsoleBitOutput("CARRY"),
			}
		)
	{
		connectors = {
			new Connector(inputs[0], 0, &xor0, 0),
			new Connector(inputs[0], 0, &and0, 0),
			new Connector(inputs[1], 0, &xor0, 1),
			new Connector(inputs[1], 0, &and0, 1),
			new Connector(&xor0, 0, outputs[0], 0),
			new Connector(&and0, 0, outputs[1], 0),
		};
		Init();
	}
};


int main()
{
	

	MyCircuit circuit;
	circuit.Update();

	return 0;
}