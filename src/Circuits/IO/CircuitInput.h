#pragma once
#include <Circuits/IO/Input.h>

#include <string>


class CircuitInput : public Input
{
protected:
	std::string name;
public:
	CircuitInput(const std::string& name) : name(name) {}

	virtual inline unsigned GetInputCount() const override { return 1; }
};


class CircuitBitInput : public CircuitInput
{
private:
	BitPort io;
public:
	CircuitBitInput(const std::string& name)
		: CircuitInput(name) {}

	virtual inline const Port* GetOutput(unsigned idx) const override { return &io; }
	virtual inline void SetInputVal(unsigned idx, void* val) override { io.SetVal(val); }
	virtual inline Port* GetInput(unsigned idx) const override { return (Port*) &io; }

	virtual void Update(unsigned flags = 0) {}
};