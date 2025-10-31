#include <Circuits/Core/Circuit.h>

#include <algorithm>

RootCircuit::RootCircuit(const std::vector<Input*>& inputs, const std::vector<Output*>& outputs)
	: inputs(inputs), outputs(outputs), updateSequence(outputs.size())
{
	
}


void RootCircuit::Init()
{
	for (int i = 0; i < outputs.size(); i++) {
		std::vector<Component*> currentPath;
		SetUpdateSequence(currentPath, 0, i, outputs[i]);
	}
}


void RootCircuit::Update()
{
	for (int i = 0; i < inputs.size(); i++) {
		inputs[i]->Update();
	}

	for (int i = 0; i < outputs.size(); i++) {
		for (int j = updateSequence[i].size() - 1; j >= 0; j--) {
			updateSequence[i][j]->Update();
		}
	}
}


RootCircuit::~RootCircuit()
{
	for (unsigned i = 0; i < inputs.size(); i++) {
		delete inputs[i];
	}

	for (unsigned i = 0; i < outputs.size(); i++) {
		delete outputs[i];
	}
}


void RootCircuit::SetUpdateSequence(std::vector<Component*>& path, unsigned offset, unsigned idx, Element* curElem)
{
	if (curElem->GetType() == Element::Input) {
		return;
	}

	updateSequence[idx].push_back(curElem);
	path.push_back(curElem);

	unsigned inputCount = curElem->GetInputCount();
	for (int i = 0; i < inputCount; i++) {
		unsigned connCount = curElem->GetInput(i)->GetConnectorsCount();
		for (int j = 0; j < connCount; j++) {
			Connector* curConnector = curElem->GetInput(i)->GetConnectorPtr(j);
			const Element* nextElem = curConnector->GetSrcElement();
			if (std::find(path.begin(), path.end(), nextElem) != path.end()) {
				throw CircuitCycleException();
			}
			updateSequence[idx].push_back(curConnector);
			SetUpdateSequence(path, offset + 1, idx, (Element *)nextElem);
		}
	}

	path.pop_back();
}