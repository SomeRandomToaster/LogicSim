#pragma once
#include "LogicGate.h"

class ConstantZero : public LogicGate
{
public:
	ConstantZero() : LogicGate(1, "00") { output.SetVal(false); }
};


class ConstantOne : public LogicGate
{
public:
	ConstantOne() : LogicGate(1, "11") { output.SetVal(true); }
};

class NotGate : public LogicGate
{
public:
	NotGate() : LogicGate(1, "10") {}
};

class OrGate : public LogicGate
{
public:
	OrGate() : LogicGate(2, "0111") {}
};

class AndGate : public LogicGate
{
public:
	AndGate() : LogicGate(2, "0001") {}
};

class NandGate : public LogicGate
{
public:
	NandGate() : LogicGate(2, "1110") {}
};

class NorGate : public LogicGate
{
public:
	NorGate() : LogicGate(2, "1000") {}
};

class XorGate : public LogicGate
{
public:
	XorGate() : LogicGate(2, "0110") {}
};

class XnorGate : public LogicGate
{
public:
	XnorGate() : LogicGate(2, "1001") {}
};

class OrGate3 : public LogicGate
{
public:
	OrGate3() : LogicGate(3, "01111111") {}
};

class AndGate3 : public LogicGate
{
public:
	AndGate3() : LogicGate(3, "00000001") {}
};