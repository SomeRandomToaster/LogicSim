#pragma once

#include <Circuits/IO/CircuitInput.h>
#include <Circuits/IO/CircuitOutput.h>
#include <Circuits/Core/Connector.h>

#include <vector>

class RootCircuit
{
	std::vector<std::vector<Component*>> updateSequence;
protected:
	std::vector <Input*> inputs;
	std::vector <Output*> outputs;
public:
	RootCircuit(const std::vector<Input*>& inputs, const std::vector<Output*>& outputs);
	virtual ~RootCircuit();

	void Init();
	void Update();
private:
	void SetUpdateSequence(std::vector<Component*>& path, unsigned offset, unsigned idx, Element* curElem);

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
