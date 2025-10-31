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
	BitPort io;
public:
	CircuitBitOutput(const std::string& name)
		: CircuitOutput(name) {
	}

	virtual inline const Port* GetOutput(unsigned idx) const override { return &io; }
	virtual inline void SetInputVal(unsigned idx, void* val) override { io.SetVal(val); }
	virtual inline Port* GetInput(unsigned idx) const override { return (Port*)&io; }

	virtual void Update() {}
};