#include "include/parser.h"
#include "include/Time.h"
#include <string>
#include <fstream>
#include <time.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "no input file specified!" << std::endl;
		return 1;
	}
	std::ifstream ifs(argv[1]);
	if (!ifs.good())
	{
		std::cout << "can't open file" << argv[1] << "!" << std::endl;
		return 1;
	}
	auto Par = 0;
	auto Solver = 0;
	ElapsedTimer t(true);
	CircuitGraph graph;
	Parser parser;
	if (!parser.parse(ifs, graph))
	{
		std::cout << "can't parse file" << argv[1] << "!" << std::endl;
		return 1;
	}
	graph.validity_check();
	graph.print_circuit_info(false, false, false, true);
	Par =  t.get_elapsed_us();
	std::cout << "the time of parser:   " << 1.0 * Par/1000 << "  ms" << std :: endl;

	return 0;
}
