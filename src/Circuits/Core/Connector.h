#pragma once
#include <Circuits/Core/Element.h>

#include <exception>
#include <iostream>


class InvalidConnectorException : public std::exception
{
	const char* what() { return "Invalid connector types combination"; }
};


class Connector : public Component
{
public:
	enum class ConnectorType
	{
		BitToBit
	};
private:
	Element* from;
	Element* to;
	const Port* fromPort;
	Port* toPort;
	ConnectorType type;
public:
	Connector(Element* from, unsigned from_idx, Element* to, unsigned to_idx)
	{
		this->from = from;
		this->to = to;
		fromPort = from->GetOutput(from_idx);
		toPort = to->GetInput(to_idx);


		if (fromPort->GetPortType() == PortType::Bit && toPort->GetPortType() == PortType::Bit) {
			type = ConnectorType::BitToBit;
		}
		else {
			throw InvalidConnectorException();
		}
		toPort->AddInConnectorPtr(this);
		((Port*)fromPort)->AddOutConnectorPtr(this);
	}
	inline ComponentType GetComponentType() const override { return ComponentType::Connector; }

	inline void Update() {
		switch (type)
		{
		case ConnectorType::BitToBit:
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