#include "connector.hpp"

int main()
{
    Connector c("www.bme.hu");
    c.discover(5);
    c.display();

    return 0;
}
