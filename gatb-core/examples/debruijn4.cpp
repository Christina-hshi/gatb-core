//! [snippet1]

// We include what we need for the test
#include <gatb/gatb_core.hpp>

/********************************************************************************/
/*             Graph creation from a fake bank and command line options         */
/********************************************************************************/
int main (int argc, char* argv[])
{
    // We get a handle on a fake bank made of 3 sequences.
    IBank* bank = new BankStrings (
        "ATCGTACGACGCTAGCTAGCA",
        "ACTACGTATCGGTATATATTTTCGATCGATCAG",
        "TGACGGTAGCATCGATCAGGATCGA",
        NULL
    );

    // We create the graph with the bank and other options
    Graph graph = Graph::create (bank, "-kmer-size 5  -out mygraph");

    // We dump some information about the graph.
    std::cout << graph.getInfo() << std::endl;

    // Note: Graph::create will take care about 'bank' object and will delete it if nobody else needs it.
    // In other words: there is no need here to call 'delete' on 'bank' here.

    return EXIT_SUCCESS;
}
//! [snippet1]
