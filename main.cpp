#include "connector.hpp"

int main()
{
    Connector c("https://infoc.eet.bme.hu/");
    //c.add_output_flag(Connector::file);
    //c.add_output_flag(Connector::outlink);
    c.discover(2);
    c.gen_dot("out.dot");

    return 0;
}
