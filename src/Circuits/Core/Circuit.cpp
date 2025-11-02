#include <Circuits/Core/Circuit.h>

#include <algorithm>
#include <queue>

RootCircuit::RootCircuit(const std::vector<Input*>& inputs, const std::vector<Output*>& outputs)
	: inputs(inputs), outputs(outputs)
{
	
}


void RootCircuit::Init()
{

	// Topological sort based on DFS
	std::set<Component*> whiteNodes = GetCircuitComponents();
	std::set<Component*> grayNodes, blackNodes;


	while (!whiteNodes.empty()) {
		TopoSortVisit(*whiteNodes.begin(), whiteNodes, grayNodes, blackNodes);
	}
	std::reverse(updateSequence.begin(), updateSequence.end());
	
	// Set update flags for connectors
	std::set<const Port*> ports;
	for (int i = updateSequence.size() - 1; i >= 0; i--) {
		if (updateSequence[i].ptr->GetComponentType() != Component::ComponentType::Connector) {
			continue;
		}

		const Connector* conn = (const Connector*)updateSequence[i].ptr;
		const Port* destPort = conn->GetDestPort();
		if (ports.find(destPort) == ports.cend()) {
			ports.insert(destPort);
			updateSequence[i].flags |= Component::LastConnectorToPort;
		}
	}
}


void RootCircuit::Update()
{
	for (auto input : inputs) {
		input->Update();
	}

	for (auto c : updateSequence) {
		c.ptr->Update();
	}

	for (auto output : outputs) {
		output->Update();
	}
}


std::set<Component*> RootCircuit::GetCircuitComponents() const
{
	// Basically just a BFS that stops at inputs and outputs
	std::queue<Component*> nodesQueue;
	std::set<Component*>visitedNodes;

	for (size_t i = 0; i < inputs.size(); i++) { // filling initial queue with connectors that start in inputs
		size_t outputsCount = inputs[i]->GetOutputCount();
		
		for (size_t j = 0; j < outputsCount; j++) {
			const Port* outputPort = inputs[i]->GetOutput(j);
			size_t connectorsCount = outputPort->GetConnectorsCount();
			
			for (size_t k = 0; k < connectorsCount; k++) {
				nodesQueue.push(outputPort->GetConnectorPtr(k));
			}
		}
	}

	while (!nodesQueue.empty()) {
		Component* curComponent = nodesQueue.front();
		nodesQueue.pop();

		if (visitedNodes.find(curComponent) != visitedNodes.cend()) { // already visited that node. Skipping.
			continue;
		}

		if (curComponent->GetComponentType() == Component::ComponentType::Element) {
			Element* elem = (Element*)curComponent;
			size_t outputsCount = elem->GetOutputCount();

			for (size_t j = 0; j < outputsCount; j++) { // add connector to the queue
				const Port* outputPort = elem->GetOutput(j);
				size_t connectorsCount = outputPort->GetConnectorsCount();

				for (size_t k = 0; k < connectorsCount; k++) {
					nodesQueue.push(outputPort->GetConnectorPtr(k));
				}
			}
		}
		else {
			Connector* conn = (Connector*)curComponent;
			Element* destElem = conn->GetDestElement();
			Element::ElementType elemType = destElem->GetElementType();
			if (elemType != Element::ElementType::Input && elemType != Element::ElementType::Output) {
				nodesQueue.push(destElem);
			}
		}
		visitedNodes.insert(curComponent);
	}

	return visitedNodes;
}


void RootCircuit::TopoSortVisit(Component* node, std::set<Component*>& whiteNodes, std::set<Component*>& grayNodes, std::set<Component*>& blackNodes) {
	if (blackNodes.find(node) != blackNodes.cend()) {
		return;
	}
	if (grayNodes.find(node) != grayNodes.cend()) {
		throw CircuitCycleException();
	}

	whiteNodes.erase(node);
	grayNodes.insert(node);

	if (node->GetComponentType() == Component::ComponentType::Element) {
		Element* elem = (Element*)node;
		size_t outputsCount = elem->GetOutputCount();

		for (size_t j = 0; j < outputsCount; j++) {
			const Port* outputPort = elem->GetOutput(j);
			size_t connectorsCount = outputPort->GetConnectorsCount();

			for (size_t k = 0; k < connectorsCount; k++) {
				TopoSortVisit(outputPort->GetConnectorPtr(k), whiteNodes, grayNodes, blackNodes);
			}
		}
	}
	else {
		Connector* conn = (Connector*)node;
		Element* destElem = conn->GetDestElement();
		Element::ElementType elemType = destElem->GetElementType();
		if (elemType != Element::ElementType::Input && elemType != Element::ElementType::Output) {
			TopoSortVisit(destElem, whiteNodes, grayNodes, blackNodes);
		}
	}

	grayNodes.erase(node);
	blackNodes.insert(node);
	updateSequence.push_back({ node, 0 });
}


RootCircuit::~RootCircuit()
{
	for (size_t i = 0; i < inputs.size(); i++) {
		delete inputs[i];
	}

	for (size_t i = 0; i < outputs.size(); i++) {
		delete outputs[i];
	}

	for (size_t i = 0; i < connectors.size(); i++) {
		delete connectors[i];
	}
}