#pragma once
#include <Circuits/Core/Element.h>

#include <exception>
#include <iostream>


class InvalidConnectorException : public std::exception
{
	const char* what() { return "Invalid connector types combination"; }
};

class PortCollisionException : public std::exception
{
	const char* what() { return "Two or more active ports are connected to the same port"; }
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
		toPort->AddConnectorPtr(this);
		((Port*)fromPort)->AddConnectorPtr(this);
	}
	inline ComponentType GetComponentType() const override { return ComponentType::Connector; }

	inline void Update(unsigned flags = 0) override {

		// check active connectors count
		size_t connectorsCount = toPort->GetConnectorsCount();
		size_t activeCount = 0;
		if (flags & LastConnectorToPort) {
			for (size_t i = 0; i < connectorsCount; i++) {
				Connector* conn = toPort->GetConnectorPtr(i);
				if (conn->GetSrcPort()->IsActive()) {
					activeCount++;
				}
			}
		}

		switch (type)
		{
		case ConnectorType::BitToBit:
			
			if (fromPort->IsActive()) {
				bool bit;
				bit = ((BitPort*)fromPort)->GetVal();
				((BitPort*)toPort)->SetVal(bit);
			}

			if (flags & LastConnectorToPort) {
				// if there's no active connectors, we must write zero to this port
				if (!activeCount) {
					((BitPort*)toPort)->SetVal(false);
				}
				else if (activeCount > 1) { // potential collision. We must check values
					bool value = false;
					bool valueSet = false;
					
					for (size_t i = 0; i < connectorsCount; i++) {
						Connector* conn = toPort->GetConnectorPtr(i);
						const Port* port = conn->GetSrcPort();
						if (port->IsActive()) {
							if (!valueSet) {
								value = ((const BitPort*)port)->GetVal();
								valueSet = true;
							}
							else if (value != ((const BitPort*)port)->GetVal()) {
								throw PortCollisionException();
							}
						}
					}
				}
				// if active count = 1, everything is fine			
			}
			break;
		default:
			break;
		}
	}
	inline void Init() {

	}
	inline const Element* GetSrcElement() { return from; }
	inline Element* GetDestElement() { return to; }
	inline const Port* GetSrcPort() const { return fromPort; }
	inline const Port* GetDestPort() const { return toPort; }
};