#pragma once
#include <Circuits/Core/Element.h>

#include <exception>
#include <iostream>

enum ConnectorMode
{
	BitToBit
};


class InvalidConnectorException : public std::exception
{
	const char* what() { return "Invalid connector types combination"; }
};


class Connector : public Component
{
	Element* from;
	Element* to;
	const Port* fromPort;
	Port* toPort;
	ConnectorMode mode;
public:
	Connector(Element* from, unsigned from_idx, Element* to, unsigned to_idx)
	{
		this->from = from;
		this->to = to;
		fromPort = from->GetOutput(from_idx);
		toPort = to->GetInput(to_idx);


		if (fromPort->GetType() == Bit && toPort->GetType() == Bit) {
			mode = BitToBit;
		}
		else {
			throw InvalidConnectorException();
		}
		toPort->AddConnectorPtr(this);
	}
	inline void Update() {
		switch (mode)
		{
		case BitToBit:
			bool bit;
			bit = ((BitPort*)fromPort)->GetVal();
			((BitPort*)toPort)->SetVal(bit);
			break;
		default:
			break;
		}
	}
	inline void Init() {

	}
	inline const Element* GetSrcElement() { return from; }
	inline Element* GetDestElement() { return to; }
};