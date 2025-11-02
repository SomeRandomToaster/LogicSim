#pragma once
#include <Circuits/Core/Element.h>


class Switch : public Element
{
protected:
	BitPort enable;
public:
	virtual inline ElementType GetElementType() const override { return ElementType::Switch; }
	virtual inline unsigned GetInputCount() const override { return 2; }
	virtual inline unsigned GetOutputCount() const override { return 1; }
};


class BitSwitch : public Switch
{
	BitPort input, output;
public:
	virtual inline void SetInputVal(unsigned idx, void* val) override 
	{ 
		if (idx) {
			enable.SetVal(*((bool*)val));
		}
		else {
			input.SetVal(*((bool*)val));
		}
	}
	virtual inline const Port* GetOutput(unsigned idx) const override { return &output; }
	virtual inline Port* GetInput(unsigned idx) const override { return (Port*)(idx ? &enable : &input); }

	void Update(unsigned flags = 0) override
	{
		output.SetActive(enable.GetVal());
		if (enable.GetVal()) {
			output.SetVal(input.GetVal());
		}
	}
};