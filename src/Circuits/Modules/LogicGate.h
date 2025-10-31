#pragma once
#include <Circuits/Core/Element.h>

#include <vector>

#define LOGIC_GATE_VALUE_COUNT(x) (1ull << x)

class LogicGate : public Element
{
private:
	const unsigned inputCount;
	std::vector<bool> valVec;
	std::vector<BitPort> inputs;
protected:
	BitPort output;
public:
	LogicGate(unsigned inputCount, const bool* vector) : inputCount(inputCount), valVec(LOGIC_GATE_VALUE_COUNT(inputCount)), inputs(inputCount)
	{
		for(int i = 0; i < LOGIC_GATE_VALUE_COUNT(inputCount); i++)
		{
			valVec[i] = vector[i];
		}
	}
	LogicGate(unsigned inputCount, const char* vector) : inputCount(inputCount), valVec(LOGIC_GATE_VALUE_COUNT(inputCount)), inputs(inputCount)
	{
		for (unsigned i = 0; i < LOGIC_GATE_VALUE_COUNT(inputCount); i++)
		{
			valVec[i] = vector[i] - '0';
		}
	}

	virtual inline unsigned GetInputCount() const override { return inputCount; }
	virtual inline unsigned GetOutputCount() const override { return 1; }
	virtual inline void SetInputVal(unsigned idx, void* val) override { inputs[idx].SetVal(*(bool *)val); }
	virtual inline const BitPort* GetOutput(unsigned idx) const override { return &output; }
	virtual inline BitPort* GetInput(unsigned idx) const override { return (BitPort*)&inputs[idx]; }
	virtual inline ElementType GetType() const { return ElementType::LogicGate; }
	
	virtual void Update() override 
	{
		unsigned idx = 0;
		for (int i = inputCount - 1; i >= 0; i--) {
			idx <<= 1;
			idx |= (unsigned)inputs[i].GetVal();
		}
		output.SetVal(valVec[idx]);
	}
};


