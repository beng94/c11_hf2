#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>
#include <set>

#include "link.hpp"
#include "graph.hpp"

class Connector
{
    private:
        Link root;
        std::set<std::string> visited;
        Graph graph;

        int depth = 0;

        void foo (Link&, const int&);
        void parse_urls (const std::string&, std::list<std::string>&);

    public:
        Connector () = delete;
        Connector (std::string);

        void discover (const int&);
        void gen_dot (std::string);
};

#endif
