#pragma once
#include <Circuits/IO/Output.h>

#include <string>


class CircuitOutput : public Output
{
protected:
	std::string name;
public:
	CircuitOutput(const std::string& name) : name(name) {}

	virtual inline unsigned GetOutputCount() const override { return 1; }
};


class CircuitBitOutput : public CircuitOutput
{
private:
	BitPort input, output;
public:
	CircuitBitOutput(const std::string& name)
		: CircuitOutput(name) {
	}

	virtual inline const Port* GetOutput(unsigned idx) const override { return &output; }
	virtual inline void SetInputVal(unsigned idx, void* val) override { input.SetVal(val); }
	virtual inline Port* GetInput(unsigned idx) const override { return (Port*)&input; }

	virtual void Update(unsigned flags = 0) { output.SetVal(input.GetVal()); }
};