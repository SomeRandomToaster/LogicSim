#pragma once
#include <Circuits/IO/Input.h>

#include <iostream>


class ConsoleInput : public Input
{
protected:
	std::string name;
	bool log;
public:
	ConsoleInput(const std::string& name, bool log = true)
		: name(name), log(log) {}

	virtual inline unsigned GetInputCount() const override { return 0; }
	virtual inline void SetInputVal(unsigned idx, void* val) override {}
	virtual inline Port* GetInput(unsigned idx) const override { return nullptr; }
};


class ConsoleBitInput : public ConsoleInput
{
private:
	BitPort output;
public:
	virtual inline const Port* GetOutput(unsigned idx) const override { return &output; }

	ConsoleBitInput(const std::string& name, bool log = true)
		: ConsoleInput(name, log) {}

	virtual void Update() {
		if (log) {
			std::cout << name << " (bit): ";
		}
		bool val;
		std::cin >> val;
		output.SetVal(val);
	}
};