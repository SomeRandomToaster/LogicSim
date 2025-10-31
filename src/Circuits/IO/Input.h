#pragma once

#include <Circuits/Core/Element.h>

#include <iostream>

class Input : public Element
{
public:
	virtual inline ElementType GetType() const { return ElementType::Input; }
	virtual inline unsigned GetOutputCount() const override { return 1; }
	virtual inline unsigned GetInputCount() const override { return 0; }
	virtual inline void SetInputVal(unsigned idx, void* val) override {}
	virtual inline Port* GetInput(unsigned idx) const override { return nullptr; }
};


class ConsoleBitInput : public Input
{
private:
	BitPort output;
	std::string name;
	bool log;
public:
	virtual inline const Port* GetOutput(unsigned idx) const override { return &output; }

	ConsoleBitInput(const std::string& name, bool log = true) 
		: name(name), log(log) {}

	virtual void Update() {
		if (log) {
			std::cout << name << " (bit): ";
		}
		bool val;
		std::cin >> val;
		output.SetVal(val);
	}
};