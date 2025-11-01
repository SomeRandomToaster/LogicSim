#include <Circuits.h>

#include <iostream>


class ComplicatedXor : public RegularCircuit
{
	NotGate not0, not1;
	AndGate and0, and1;
	OrGate or0;

public:
	ComplicatedXor()
		: RegularCircuit(
			{
				new CircuitBitInput("IN1"),
				new CircuitBitInput("IN2")
			},
			{
				new CircuitBitOutput("OUT"),
			}
			)
	{
		connectors = {
			new Connector(inputs[0], 0, &not0, 0),
			new Connector(inputs[1], 0, &not1, 0),
			new Connector(&not0, 0, &and0, 0),
			new Connector(inputs[1], 0, &and0, 1),
			new Connector(inputs[0], 0, &and1, 0),
			new Connector(&not1, 0, &and1, 1),
			new Connector(&and0, 0, &or0, 0),
			new Connector(&and1, 0, &or0, 1),
			new Connector(&or0, 0, outputs[0], 0),
		};
		Init();
	}
};


class HalfAdder : public RegularCircuit
{
	ComplicatedXor xor0;
	AndGate and0;


public:
	HalfAdder()
		: RegularCircuit(
			{
				new CircuitBitInput("IN1"),
				new CircuitBitInput("IN2")
			}, 
			{
				new CircuitBitOutput("SUM"),
				new CircuitBitOutput("CARRY"),
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


class MyCircuit : public RootCircuit {
	HalfAdder adder1, adder2;
public:
	MyCircuit()
		: RootCircuit(
			{
				new ConsoleBitInput("A"),
				new ConsoleBitInput("B"),
				new ConsoleBitInput("C"),
				new ConsoleBitInput("D"),
			},
			{
				new ConsoleBitOutput("S1"),
				new ConsoleBitOutput("C1"),
				new ConsoleBitOutput("S2"),
				new ConsoleBitOutput("C2")
			}
			) 
	{
		connectors = {
			new Connector(inputs[0], 0, &adder1, 0),
			new Connector(inputs[1], 0, &adder1, 1),
			new Connector(&adder1, 0, outputs[0], 0),
			new Connector(&adder1, 1, outputs[1], 0),

			new Connector(inputs[2], 0, &adder2, 0),
			new Connector(inputs[3], 0, &adder2, 1),
			new Connector(&adder2, 0, outputs[2], 0),
			new Connector(&adder2, 1, outputs[3], 0),

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