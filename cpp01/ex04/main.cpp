#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    if (s1.empty())
    {
        std::cerr << "s1 must not be empty." << std::endl;
        return 1;
    }

    std::ifstream input(filename.c_str());
    if (!input)
    {
        std::cerr << "cannot open input file '" << filename << "'" << std::endl;
        return 1;
    }

    std::ofstream output((filename + ".replace").c_str());
    if (!output)
    {
        std::cerr << "cannot create output file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(input, line))
    {
        std::string result;
        std::size_t pos = 0;
        std::size_t found;

        while ((found = line.find(s1, pos)) != std::string::npos)
        {
            result.append(line, pos, found - pos);
            result.append(s2);
            pos = found + s1.length();
        }
        result.append(line, pos, line.length() - pos);
        output << result;
        if (!input.eof())
            output << '\n';
    }

    input.close();
    output.close();
    return 0;
}
