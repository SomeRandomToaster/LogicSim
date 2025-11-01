#pragma once

#include <Circuits/Core/Element.h>

#include <iostream>

class Output : public Element
{
public:
	virtual inline ElementType GetElementType() const override { return ElementType::Output; }
	virtual inline unsigned GetInputCount() const { return 1; }
};


