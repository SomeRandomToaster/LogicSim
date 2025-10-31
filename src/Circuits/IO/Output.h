#pragma once

#include <Circuits/Core/Element.h>

#include <iostream>

class Output : public Element
{
public:
	virtual inline ElementType GetType() const override { return ElementType::Output; }
	virtual inline unsigned GetInputCount() const { return 1; }
	virtual inline unsigned GetOutputCount() const override { return 0; }
	virtual inline const Port* GetOutput(unsigned idx) const { return nullptr; }
};


class ConsoleBitOutput : public Output
{
private:
	BitPort input;
	std::string name;
	bool log;
public:
	virtual inline void SetInputVal(unsigned idx, void* val) { input.SetVal(val); }
	virtual inline Port* GetInput(unsigned idx) const override { return (BitPort*)&input; }

	ConsoleBitOutput(const std::string& name, bool log = true)
		: name(name), log(log) {}

	virtual void Update() {
		if (log) {
			std::cout << name << " (bit): ";
		}
		std::cout << input.GetVal() << std::endl;
	}
};