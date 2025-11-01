#pragma once
#include <Circuits/Core/Element.h>

class Input : public Element
{
public:
	virtual inline ElementType GetElementType() const override { return ElementType::Input; }
	virtual inline unsigned GetOutputCount() const override { return 1; }
};