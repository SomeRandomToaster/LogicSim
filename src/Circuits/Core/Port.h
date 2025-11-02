#pragma once
#include <cstdint>
#include <vector>

enum class PortType
{
	Bit
};

class Connector;

class Port
{
private:
	std::vector<Connector*> connectors;
public:
	virtual inline PortType GetPortType() const = 0;
	virtual inline size_t GetConnectorsCount() const { return connectors.size(); }
	virtual inline Connector* GetConnectorPtr(unsigned idx) const { return connectors[idx]; }
	virtual inline void AddConnectorPtr(Connector* ptr) { connectors.push_back(ptr); }
};


class BitPort : public Port
{
private:
	bool val = 0;
public:
	inline bool GetVal() const { return val; }
	inline void SetVal(bool newVal) { val = newVal; }
	virtual inline PortType GetPortType() const override { return PortType::Bit; }
};