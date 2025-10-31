#pragma once
#include <Circuits/IO/Input.h>


class ConstantInput : public Input
{
public:
	virtual inline unsigned GetInputCount() const override { return 0; }
	virtual inline void SetInputVal(unsigned idx, void* val) override {}
	virtual inline Port* GetInput(unsigned idx) const override { return nullptr; }
};


class ConstantBitInput : public ConstantInput
{
private:
	BitPort output;
public:
	ConstantBitInput(bool value) { output.SetVal(value); }

	virtual inline const Port* GetOutput(unsigned idx) const override { return &output; }
};