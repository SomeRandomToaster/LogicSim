#pragma once
#include <Circuits/Core/Circuit.h>
#include <Circuits/Modules/BinaryLogic.h>


class HalfAdder : public RegularCircuit
{
	XorGate xor0;
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

	virtual inline ElementType GetElementType() const override { return ElementType::Arithmetic; }
};


class BitAdder : public RegularCircuit
{
	XorGate xor0, xor1;
	AndGate and0, and1, and2;
	OrGate3 or0;


public:
	BitAdder()
		: RegularCircuit(
			{
				new CircuitBitInput("IN0"),
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
			new Connector(inputs[1], 0, &xor0, 1),
			new Connector(&xor0, 0, &xor1, 0),
			new Connector(inputs[2], 0, &xor1, 1),
			new Connector(&xor1, 0, outputs[0], 0),

			new Connector(inputs[0], 0, &and0, 0),
			new Connector(inputs[1], 0, &and0, 1),
			new Connector(inputs[0], 0, &and1, 0),
			new Connector(inputs[2], 0, &and1, 1),
			new Connector(inputs[1], 0, &and2, 0),
			new Connector(inputs[2], 0, &and2, 1),
			new Connector(&and0, 0, &or0, 0),
			new Connector(&and1, 0, &or0, 1),
			new Connector(&and2, 0, &or0, 2),
			new Connector(&or0, 0, outputs[1], 0),
		};
		Init();
	}

	virtual inline ElementType GetElementType() const override { return ElementType::Arithmetic; }
};