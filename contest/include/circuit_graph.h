#include <string>
#include <cstdint>
#include <limits>
#include <vector>
#include <set>
#include <unordered_map>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

#ifndef CIRCUIT_GRAPH_H
#define CIRCUIT_GRAPH_H
#pragma once

#define NULL_INDEX -1

using gate_idx = int;
using line_idx = int; 

class Gate;
class CircuitGraph;

struct Line
{
	void connect_as_input(gate_idx gate)
	{
		destination_gates.insert(gate);
	}
	std::string name;
	int id_line = NULL_INDEX;

	gate_idx source = NULL_INDEX;         // nullptr means input port
	std::set<gate_idx> destination_gates;

	bool is_input = false;
	bool is_output = false;
};

class Gate
{
public:
	Gate(line_idx output, std::vector<line_idx> &&inputs);                

	const std::vector<line_idx> &get_inputs() const { return m_inputs; }
	std::vector<line_idx> &inputs() { return m_inputs; }

	const line_idx &get_output() const { return m_output; }
	line_idx &output() { return m_output; }

	const bool &get_reg() const { return is_reg; }
	bool &reg() { return is_reg; }

	const std::string &get_name() const { return m_name; }
	std::string  &name() { return m_name; }

private:
	bool is_reg = false;
    std::string m_name;
	std::vector<line_idx> m_inputs;    //如果是reg，按照CLK、D、RESET的顺序储存
	line_idx m_output = NULL_INDEX;
};

class CircuitGraph
{
public:
	CircuitGraph()
	{
		m_gates.reserve(100000u);
		m_lines.reserve(100000u);
		m_inputs.reserve(200u);
		m_outputs.reserve(200u);
		m_regs.reserve(10000u);
	}
	line_idx add_input(const std::string &name);
	line_idx add_output(const std::string &name);
	line_idx add_wire(const std::string &name);
	gate_idx add_gate(const std::string& gate_name, const std::vector<std::string> &input_names, const std::string &output_name, bool is_reg);

	const line_idx get_line(const std::string &name) const;
	line_idx line(const std::string &name);

	const Gate& get_gate(const gate_idx& idx) const { return m_gates[idx]; }
	Gate& gate(const gate_idx& idx) { return m_gates[idx]; }

	const Line& get_line(const line_idx &idx) const { return m_lines[idx]; }
	Line& line(const line_idx &idx) { return m_lines[idx]; }

	const std::vector<line_idx> &get_inputs() const { return m_inputs; }
	std::vector<line_idx> &inputs() { return m_inputs; }
	
	const std::vector<line_idx> &get_outputs() const { return m_outputs; }
	std::vector<line_idx> &outputs() { return m_outputs; }

	const std::vector<Gate> &get_gates() const { return m_gates; }
	std::vector<Gate> &get_gates() { return m_gates; }
	
	const std::vector<Line> &get_lines() const { return m_lines; }
	std::vector<Line> &lines() { return m_lines; }

	const std::vector<gate_idx> &get_regs() const { return m_regs; };
	std::vector<gate_idx> &regs() { return m_regs; }

public:
	// 判断有无悬空节点
	bool validity_check();
	// 打印函数
	void print_circuit_info(bool input, bool output, bool wire, bool nodes);

private:
	line_idx ensure_line(const std::string &name);

private:
	std::vector<Line> m_lines;
	std::vector<Gate> m_gates;

	std::vector<line_idx> m_inputs;
	std::vector<line_idx> m_outputs;
	std::vector<gate_idx> m_regs;

	std::unordered_map<std::string, line_idx> m_name_to_line_idx;
};
#endif