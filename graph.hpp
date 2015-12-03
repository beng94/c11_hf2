#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <list>
#include <iostream>
#include <fstream>

class Graph
{
    private:
        std::map<std::string, std::list<std::string>> LUT;

    public:
        Graph () = default;

        void insert (const std::string& src, const std::string dst)
        {
            LUT[src].push_back(dst);
        }

        void print (std::string fname)
        {
            std::ofstream file(fname);

            file << "digraph\n";
            file << "{\n";
            std::cout << "monkey" << std::endl;
            for (auto p: LUT)
            {
                std::string src = p.first;
                for (auto dst: p.second)
                {
                    file << "\t\"" << src << "\" -> \"" << dst << "\";" << std::endl;
                }
            }
            file << "}";

            file.close();
            std::cout << LUT.size() << std::endl;
        }
};

#endif
