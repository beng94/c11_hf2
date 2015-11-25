#include "connector.hpp"
#include "htmlparser.hpp"
#include "link.hpp"

Connector::Connector (std::string root) : root{root} {}

void Connector::discover (int n)
{
    Link root_link(root);
    HTMLParser parser(root_link.get_source());
    std::set<Link> links = parser.parse();

    std::set<Link> tmp_links;
    for (int i = 0; i < n; i++)
    {
        for (auto l: links)
        {
            HTMLParser p(l.get_source());
            std::set<Link> new_links = p.parse();
            //TODO: check whether we've alredy found them

            tmp_links.insert(new_links.begin(), new_links.end());
        }

        links = tmp_links;
    }
}

void Connector::display()
{

}
