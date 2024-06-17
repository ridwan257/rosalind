#include <iostream>
#include "fetch.hpp"







int main()
{
    char url1[] = "https://rest.uniprot.org/uniprotkb/B5ZC00.fasta";
    char url2[] = "https://www.google.com/";


    Response res = fetch_data(url1);

    std::cout << res.size << std::endl;

    

    return 0;
}