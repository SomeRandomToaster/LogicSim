# LogicSim
Binary logic simulation program. Maybe it will be something better.

# How it works

## Basic structure
A circuit consists of components.
Each component is an element or a connector.
An element has input and output ports.
Input ports are connected to output ports via connectors.
An element can be an input, an output or a regular element.

## Input and output
Available input and output types:
1. Console I/O
2. Constant values (input only)
3. Circuit I/O pins

## Regular elements
Available regular element types:
1. Logic gates
2. Switches
3. Arithmetic

## Circuits
A circuit has a set of input and outputs.
Each circuit automatically handles update routines of components located between inputs and outputs.
There are two types of circuits: root circuits and regular circuits. A regular circuit can have only I/O pins. A root circuit can have I/O of any type.
A regular circuit is an element and can be used in other circuits.