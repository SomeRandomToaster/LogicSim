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
		toPort->AddConnectorPtr(this);
		((Port*)fromPort)->AddConnectorPtr(this);
	}
	inline ComponentType GetComponentType() const override { return ComponentType::Connector; }

	inline void Update(unsigned flags = 0) override {
		switch (type)
		{
		case ConnectorType::BitToBit:
			if (fromPort->IsActive()) {
				bool bit;
				bit = ((BitPort*)fromPort)->GetVal();
				((BitPort*)toPort)->SetVal(bit);
			}
			else if (flags & LastConnectorToPort) {
				// check if someone has updated this port
				bool noUpdates = true;

				size_t connectorsCount = toPort->GetConnectorsCount();
				for (size_t i = 0; i < connectorsCount; i++) {
					Connector* conn = toPort->GetConnectorPtr(i);
					if (conn->GetSrcPort()->IsActive()) {
						noUpdates = false;
						break;
					}
				}
				// if no one has, we must do it
				if (noUpdates) {
					((BitPort*)toPort)->SetVal(false);
				}
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