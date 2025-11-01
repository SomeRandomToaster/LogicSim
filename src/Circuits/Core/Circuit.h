#pragma once

#include <Circuits/IO/CircuitInput.h>
#include <Circuits/IO/CircuitOutput.h>
#include <Circuits/Core/Connector.h>

#include <vector>
#include <set>

class RootCircuit
{
	std::vector<Component*> updateSequence;
protected:
	std::vector <Input*> inputs;
	std::vector <Output*> outputs;
	std::vector <Connector*> connectors;
public:
	RootCircuit(const std::vector<Input*>& inputs, const std::vector<Output*>& outputs);
	virtual ~RootCircuit();

	void Init();
	void Update();
private:
	std::set<Component*> GetCircuitComponents() const;
	void TopoSortVisit(Component* node, std::set<Component*>& whiteNodes, std::set<Component*>& grayNodes, std::set<Component*>& blackNodes);
};


class RegularCircuit : public RootCircuit
{
public:
	RegularCircuit(const std::vector<CircuitInput*>& inputs, const std::vector<CircuitOutput*>& outputs)
		: RootCircuit(std::vector<Input*>(inputs.begin(), inputs.end()), std::vector<Output*>(outputs.begin(), outputs.end())) {
	}
};


class CircuitCycleException : public std::exception
{
	const char* what() { return "A cycle is detected in circuit"; }
};
