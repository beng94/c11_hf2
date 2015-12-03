#include "connector.hpp"

int main()
{
    Connector c("https://infoc.eet.bme.hu/");
    c.discover(2);
    c.gen_dot("out.dot");

    return 0;
}
