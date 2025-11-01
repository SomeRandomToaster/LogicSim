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
	std::vector<Connector*> inConnectors;
	std::vector<Connector*> outConnectors;
public:
	virtual inline PortType GetPortType() const = 0;
	virtual inline size_t GetInConnectorsCount() const { return inConnectors.size(); }
	virtual inline size_t GetOutConnectorsCount() const { return outConnectors.size(); }
	virtual inline Connector* GetInConnectorPtr(unsigned idx) const { return inConnectors[idx]; }
	virtual inline Connector* GetOutConnectorPtr(unsigned idx) const { return outConnectors[idx]; }
	virtual inline void AddInConnectorPtr(Connector* ptr) { inConnectors.push_back(ptr); }
	virtual inline void AddOutConnectorPtr(Connector* ptr) { outConnectors.push_back(ptr); }
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