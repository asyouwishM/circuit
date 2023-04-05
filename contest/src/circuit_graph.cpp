#include "../include/circuit_graph.h"
#include <iostream>
#include <sstream>
#include <map>
#include <set>


//构造普通门
Gate::Gate(line_idx output, std::vector<line_idx> &&inputs) : m_inputs(inputs), m_output(output){}

line_idx CircuitGraph::add_input(const std::string& name)
{
	line_idx p_line = ensure_line(name);
	if (!m_lines[p_line].is_input) 
	{
		m_lines[p_line].is_input = true;
		m_inputs.push_back(p_line);
	}
	return p_line;
}

line_idx CircuitGraph::add_output(const std::string& name)
{
	line_idx p_line = ensure_line(name);
	if (!m_lines[p_line].is_output) 
	{
		m_lines[p_line].is_output = true;
		m_outputs.push_back(p_line);
	}
	return p_line;
}

line_idx CircuitGraph::add_wire(const std::string& name)
{
	line_idx p_line = ensure_line(name);
	return p_line;
}

gate_idx CircuitGraph::add_gate(const std::string& gate_name, const std::vector<std::string> &input_names, const std::string &output_name, bool is_reg)
{
	std::vector<line_idx> inputs;
	for (size_t i = 0; i < input_names.size(); ++i) 
	{
		inputs.push_back(m_name_to_line_idx.find(input_names[i])->second);
	}

	line_idx p_output = m_name_to_line_idx.find(output_name)->second;
	
	m_gates.emplace_back(p_output, std::move(inputs));
	m_gates.back().reg() = is_reg;
	m_gates.back().name() = gate_name;
	gate_idx gate = m_gates.size() - 1;
	m_lines[p_output].source = gate;

	for (size_t i = 0; i < m_gates[gate].get_inputs().size(); ++i) {
			m_lines[m_gates[gate].get_inputs().at(i)].connect_as_input(gate);
		}
	return gate;
}

line_idx CircuitGraph::line(const std::string &name)
{
	auto it = m_name_to_line_idx.find(name);

	if (it != m_name_to_line_idx.end())
	{
		return it->second;
	}

	return NULL_INDEX;
}

const line_idx CircuitGraph::get_line(const std::string &name) const
{
	auto it = m_name_to_line_idx.find(name);

	if (it != m_name_to_line_idx.end())
	{
		return it->second;
	}
	return NULL_INDEX;
}

line_idx CircuitGraph::ensure_line(const std::string& name)
{
	auto it = m_name_to_line_idx.find(name);

	if (it != m_name_to_line_idx.end()) {
                return it->second; 		// 如果名为name的元素已经存在于m_name_to_line_idx中，则返回它的值，即该元素的value。
        }

	m_lines.emplace_back();
	Line& line = m_lines.back();

	line.name = name;
	line.id_line = m_lines.size() - 1;

	m_name_to_line_idx[name] = m_lines.size() - 1;

	return line.id_line;
}

bool CircuitGraph::validity_check()
{
	//原始输出线不一定没有分支
	for(const auto& line : m_lines)
	{
		if(line.is_input && line.source != NULL_INDEX)
		{
			std::cout << "There is an illegal node 1!" << std::endl;
			return false;
		}
	}
	return true;
}

void CircuitGraph::print_circuit_info(bool input, bool output, bool wire, bool nodes)
{
	//打印输入信息
	if(input)
	{
		for(const auto& input : m_inputs)
		{
			Line& temp = m_lines[input];
			if(!temp.is_input)
			{
				std::cout << "Abnormal input line!" << std::endl;
				return;
			}
			std::cout << "input " << temp.name << std::endl;
		}
	}
	//打印输出信息
	if(output)
	{
		for(const auto& output : m_outputs)
		{
			Line& temp = m_lines[output];
			if(!temp.is_output)
			{
				std::cout << "Abnormal output line!" << std::endl;
				return;
			}
			std::cout << "output " << temp.name << std::endl;
		}
	}
	//打印wire信息
	if(wire)
	{
		for(const auto& wire : m_lines)
		{
			std::cout << "wire " << wire.name << std::endl;
		}
	}
	//打印Nodes信息
	if(nodes)
	{
		for(const auto& node : m_gates)
		{
			std::cout << node.get_name() << " (";
			for(const auto& input : node.get_inputs())
			{
				std::cout << m_lines[input].name << ", ";
			}
			std::cout << m_lines[node.get_output()].name << ")" << std::endl;
		}
	}
	std::cout << "nodes num: " << m_gates.size() << "  lines num: " << m_lines.size() << std::endl;
}
