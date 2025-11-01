#include <Circuits.h>

#include <iostream>




class MyCircuit : public RootCircuit {
	FullAdder1 adder1, adder2;
public:
	MyCircuit()
		: RootCircuit(
			{
				new ConsoleBitInput("A0"),
				new ConsoleBitInput("A1"),
				new ConsoleBitInput("B0"),
				new ConsoleBitInput("B1"),
			},
			{
				new ConsoleBitOutput("S0"),
				new ConsoleBitOutput("S1"),
				new ConsoleBitOutput("C"),
			}
			) 
	{
		connectors = {
			new Connector(inputs[0], 0, &adder1, 1),
			new Connector(inputs[2], 0, &adder1, 2),
			new Connector(inputs[1], 0, &adder2, 1),
			new Connector(inputs[3], 0, &adder2, 2),
			new Connector(&adder1, 1, &adder2, 0),
			new Connector(&adder1, 0, outputs[0], 0),
			new Connector(&adder2, 0, outputs[1], 0),
			new Connector(&adder2, 1, outputs[2], 0),

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