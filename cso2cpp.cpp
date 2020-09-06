#include <fstream>
#include <cstdio>
#include <sstream>

int main(int argc, char** argv)
{
	try
	{
		if (argc != 2)
		{
			printf("Invalid number of arguments\n");
			return 0;
		}

		std::fstream is(argv[1], std::ios_base::in | std::ios_base::binary);
		std::fstream os("cso2cppOUTPUT.txt", std::ios_base::out | std::ios_base::binary);
		os << "constexpr const uint8_t data[] = {";
		bool first = true;
		while (true)
		{
			int c = is.get();
			if (c == EOF) break;
			if (first) first = false;
			else os << ',';
			std::stringstream ss;
			ss << c;
			os << ss.str();
		}
		os << "};";
		os.flush();
	}
	catch (const std::exception& e)
	{
		printf("Error: %s\n", e.what());
	}
	catch (...)
	{
		printf("Error: (unknown)\n");
	}
}