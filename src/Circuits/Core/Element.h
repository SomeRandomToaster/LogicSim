#pragma once
#include <Circuits/Core/Port.h>

#include <cstdint>

class Component
{
public:
	virtual ~Component() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	
};


class Element : public Component
{
public:
	enum ElementType
	{
		Input, Output, LogicGate
	};

	virtual void Init() {}
	virtual void Update() {}

	virtual inline ElementType GetType() const = 0;
	virtual inline unsigned GetInputCount() const = 0;
	virtual inline unsigned GetOutputCount() const = 0;
	virtual inline void SetInputVal(unsigned idx, void *val) = 0;
	virtual inline const Port* GetOutput(unsigned idx) const = 0;
	virtual inline Port* GetInput(unsigned idx) const = 0;
};