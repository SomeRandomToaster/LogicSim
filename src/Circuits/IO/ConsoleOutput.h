#pragma once
#include <Circuits/IO/Output.h>


class ConsoleOutput : public Output
{
protected:
	std::string name;
	bool log;
public:
	ConsoleOutput(const std::string& name, bool log = true)
		: name(name), log(log) {}

	virtual inline unsigned GetOutputCount() const override { return 0; }
	virtual inline const Port* GetOutput(unsigned idx) const { return nullptr; }
};


class ConsoleBitOutput : public ConsoleOutput
{
private:
	BitPort input;
public:
	virtual inline void SetInputVal(unsigned idx, void* val) { input.SetVal(val); }
	virtual inline Port* GetInput(unsigned idx) const override { return (BitPort*)&input; }

	ConsoleBitOutput(const std::string& name, bool log = true)
		: ConsoleOutput(name, log) {}

	virtual void Update(unsigned flags = 0) {
		if (log) {
			std::cout << name << " (bit): ";
		}
		std::cout << input.GetVal() << std::endl;
	}
};