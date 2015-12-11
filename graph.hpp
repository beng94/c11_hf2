#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <list>
#include <iostream>
#include <fstream>

enum NodeFlag
{
    file,
    outlink
};

class Graph
{
    private:
        std::map<std::string, std::list<std::string>> LUT;
        std::map<std::string, NodeFlag> flags;

    public:
        Graph () = default;

        /* Elmenti, hogy a node fájl, vagy kifelé mutató link. */
        void add_flag (const std::string& node, const NodeFlag& flag)
        {
            flags[node] = flag;
        }

        /* Visszaadja a NodeFlag-hez tartozó szöveges típust. */
        std::string get_props (const NodeFlag& flag)
        {
            switch (flag)
            {
                case file: return "style=filled, fillcolor=green";
                case outlink: return "style=filled, fillcolor=blue";
            }
        }

        /* Beszúr egy új élet a gráfba. */
        void insert (const std::string& src, const std::string dst)
        {
            LUT[src].push_back(dst);
        }

        /* Kiírja a gráfot egy dot fájlba. */
        void print (std::string fname)
        {
            std::ofstream file(fname);

            file << "digraph\n";
            file << "{\n";
            file << "\tgraph[outputorder=edgesfirst, layout=twopi, overlap=false]" << std::endl;
            file << "\tnode[style=filled]" << std::endl;

            for (auto f: flags)
            {
                file << "\t\"" << f.first << "\" [" << get_props(f.second) << "]\n";
            }
            file << std::endl;

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
