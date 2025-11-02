#pragma once

#include <Circuits/IO/CircuitInput.h>
#include <Circuits/IO/CircuitOutput.h>
#include <Circuits/Core/Connector.h>

#include <vector>
#include <set>

class RootCircuit
{
	struct UpdateInfo
	{
		Component* ptr;
		unsigned flags = 0;
	};

	std::vector<UpdateInfo> updateSequence;
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


class RegularCircuit : public RootCircuit, public Element
{
public:
	RegularCircuit(const std::vector<CircuitInput*>& inputs, const std::vector<CircuitOutput*>& outputs)
		: RootCircuit(std::vector<Input*>(inputs.begin(), inputs.end()), std::vector<Output*>(outputs.begin(), outputs.end())) {
	}

	virtual inline ElementType GetElementType() const { return ElementType::Circuit; }
	virtual inline unsigned GetInputCount() const { return inputs.size(); }
	virtual inline unsigned GetOutputCount() const { return outputs.size(); }
	virtual inline void SetInputVal(unsigned idx, void* val) { inputs[idx]->SetInputVal(0, val); }
	virtual inline const Port* GetOutput(unsigned idx) const { return outputs[idx]->GetOutput(0); }
	virtual inline Port* GetInput(unsigned idx) const { return inputs[idx]->GetInput(0); }

	virtual inline void Init() override { RootCircuit::Init(); }
	virtual inline void Update(unsigned flags = 0) override { RootCircuit::Update(); }
};


class CircuitCycleException : public std::exception
{
	const char* what() { return "A cycle is detected in circuit"; }
};
