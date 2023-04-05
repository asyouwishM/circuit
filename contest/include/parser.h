#include <iostream>
#include "circuit_graph.h"
#include "myfunction.h"

#ifndef PARSER_H
#define PARSER_H

class Parser
{
public:
	bool parse(std::istream& is, CircuitGraph& graph);

private:
	bool match_input(CircuitGraph& graph, const std::string& line);
	bool match_output(CircuitGraph& graph, const std::string& line);
	bool match_wire(CircuitGraph& graph, const std::string& line);
	bool match_node(CircuitGraph& graph, const std::string& line);
};


#endif