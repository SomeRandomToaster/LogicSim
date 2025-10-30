#pragma once

#include "Input.h"
#include "Output.h"
#include "Connector.h"

#include <vector>

class Circuit
{
private:
	std::vector <Input*> inputs;
	std::vector <Output*> outputs;

	std::vector<std::vector<Component*>> updateSequence;
private:
	void SetUpdateSequence(std::vector<Component*>& path, unsigned offset, unsigned idx, Element* curElem);
public:
	Circuit(const std::vector<Input*>& inputs, const std::vector<Output*>& outputs);
	void Update();
};


class CircuitCycleException : public std::exception
{
	const char* what() { return "A cycle is detected in circuit"; }
};
