#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>
#include <set>

#include "link.hpp"
#include "graph.hpp"

class Connector
{
    private:
        std::set<std::string> visited;
        Link root;
        Graph graph;
        int flags = 0;
        int depth = 0;

        void foo (Link&, const int&);
        void parse_urls (const std::string&, std::list<std::string>&);

    public:
        enum Flag
        {
            file = 1,
            outlink = 2
        };

        Connector () = delete;
        Connector (std::string);

        void add_output_flag(Connector::Flag);
        void discover (const int&);
        void gen_dot (std::string);
};

#endif
