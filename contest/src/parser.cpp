#include "../include/parser.h"

bool Parser::parse(std::istream &is, CircuitGraph &graph) 
{
  const std::string flag_input = "input";
  const std::string flag_output = "output";
  const std::string flag_wire = "wire";
  const std::string flag_node = "sky130";
  const std::string flag_end = ";";
  std::string temp{""};
  int flag = 0;
  for (std::string line; std::getline(is, line, '\n');) 
  {
    if(flag == 0)
    {    
      if (line.find(flag_input) != std::string::npos)
      {
        match_input(graph, line);
        continue;
      }
      if (line.find(flag_output) != std::string::npos)
      {
        match_output(graph, line);
        continue;
      }
      if (line.find(flag_wire) != std::string::npos)
      {
        match_wire(graph, line);
        continue;
      }
    }

    if (line.find(flag_node) != std::string::npos)
      flag = 1;

    if(flag == 1)
    {
      temp += line;
      if(line.find(flag_end) != std::string::npos)
      {
        match_node(graph, temp);
        temp = "";
        flag = 0;
        continue;
      }
    }
  }
  return true;
}

bool Parser::match_input(CircuitGraph &graph, const std::string &line) 
{
  if (line.find("input") == std::string::npos || line.find(";") == std::string::npos) 
  {
    std::cout << "the input statement format is wrong!" << std::endl;
    return false;
  }
  //input [31:0] i_numerator;
  //input i_clk;      
  std::vector<std::string> inputs_info = m_split(line, " ;");
  if(inputs_info.size() == 2)
  {
    graph.add_input(inputs_info[1]);
    return true;
  }
  std::vector<std::string> num = m_split(inputs_info[1], "[:]");
  for(int i = std::stoi(num[1]); i <= std::stoi(num[0]); i++)
  {
    graph.add_input(inputs_info[2] + "[" + std::to_string(i) + "]");
  }
  return true;
}

bool Parser::match_output(CircuitGraph &graph, const std::string &line) 
{
  if (line.find("output") == std::string::npos || line.find(";") == std::string::npos) 
  {
    std::cout << "the output statement format is wrong!" << std::endl;
    return false;
  }
  //output o_busy;
  //output [3:0] o_flags;    
  std::vector<std::string> outputs_info = m_split(line, " ;");
  if(outputs_info.size() == 2)
  {
    graph.add_output(outputs_info[1]);
    return true;
  }
  std::vector<std::string> num = m_split(outputs_info[1], "[:]");
  for(int i = std::stoi(num[1]); i <= std::stoi(num[0]); i++)
  {
    graph.add_output(outputs_info[2] + "[" + std::to_string(i) + "]");
  }
  return true;
}

bool Parser::match_wire(CircuitGraph &graph, const std::string &line) 
{
  if (line.find("wire") == std::string::npos || line.find(";") == std::string::npos) 
  {
    std::cout << "the wire statement format is wrong!" << std::endl;
    return false;
  }
  //wire o_busy;
  //wire [3:0] o_flags;    
  std::vector<std::string> wires_info = m_split(line, " ;");
  if(wires_info.size() == 2)
  {
    graph.add_wire(wires_info[1]);
    return true;
  }
  std::vector<std::string> num = m_split(wires_info[1], "[:]");
  for(int i = std::stoi(num[1]); i <= std::stoi(num[0]); i++)
  {
    int temp = graph.add_wire(wires_info[2] + "[" + std::to_string(i) + "]");
    if(graph.get_lines()[temp].is_input || graph.get_lines()[temp].is_input)
      break;
  }
  return true;
}

bool Parser::match_node(CircuitGraph &graph, const std::string &line) 
{
  if (line.find("sky130") == std::string::npos || line.find(";") == std::string::npos) 
  {
    std::cout << "the assign statement format is wrong!" << std::endl;
    return false;
  }
  auto idx = line.find('(');
  std::string node_name = m_split(line.substr(0, idx), " ")[1];
  std::string info = line.substr(idx);
  delete_space(info);
  std::vector<std::string> node_info = m_split(info, "()");
  std::vector<std::string> inputs_name;
  std::string output_name;
  bool is_reg = false;

  
  //处理寄存器
  if(node_info[0].find("CLK") != std::string::npos)
  {
    is_reg = true;
    //带reset信号的寄存器
    if(node_info.size() == 9)
    {
      inputs_name.push_back(node_info[1]);
      inputs_name.push_back(node_info[3]);
      output_name = (node_info[5]);
      inputs_name.push_back(node_info[7]);
      graph.add_gate(node_name, inputs_name, output_name, is_reg);
      return true;
    }
  }
  //处理常规节点和不带reset信号的寄存器
  node_info.pop_back();
  output_name = node_info.back();
  node_info.pop_back();

  for(int i = 0; i < node_info.size() - 1; i++)
  {
    if(i % 2 == 1)
    {
      inputs_name.push_back(node_info[i]);
    }
  }
  graph.add_gate(node_name, inputs_name, output_name, is_reg);
  return true;
}
