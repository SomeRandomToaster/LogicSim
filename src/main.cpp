#include <Circuits.h>

#include <iostream>




class MyCircuit : public RootCircuit {
	BitSwitch sw0, sw1;
	NotGate not0, not1;
public:
	MyCircuit()
		: RootCircuit(
			{
				new ConsoleBitInput("IN1"),
				new ConsoleBitInput("IN2")
			},
			{
				new ConsoleBitOutput("OUT")
			}
			) 
	{
		connectors = {
			new Connector(inputs[0], 0, &not0, 0),
			new Connector(inputs[1], 0, &not1, 0),
			new Connector(inputs[0], 0, &sw0, 0),
			new Connector(inputs[1], 0, &sw1, 0),
			new Connector(&not1, 0, &sw0, 1),
			new Connector(&not0, 0, &sw1, 1),
			new Connector(&sw0, 0, outputs[0], 0),
			new Connector(&sw1, 0, outputs[0], 0),
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