#ifndef funcs_calcpp

#define funcs_calcpp

// A namespace for commands
namespace comms {
    const unsigned short ADD = 1;
    const unsigned short MUL = 2;
    const unsigned short MEAN = 3;

    const unsigned short CLEAR = 4;
    const unsigned short DEL = 5;

    const unsigned short MAX = 6;
    const unsigned short MIN = 7;

    const unsigned short OTN = 8;
    const unsigned short NTO = 9;

    const unsigned short LOOP = 10;

    const unsigned short DIV = 11;
    const unsigned short SUB = 12;

    const unsigned short FILL = 13;

    // If the input shouldn't be changed, this will be set
    // This means, most of the time, they put a _ on the end of the comamnd
    const unsigned short NOCHANGE = 0xF0;
}

bool isNumber(std::string s);
    
// Display the vector in a readable way. If not the main vector, we should use a different "theme?"
void dispVec ( const std::vector<double> &input, bool mainVec = true );
// Handle all of the operations
std::vector<double> process ( const std::vector<double> &input, unsigned short command );
// If the command ends with a '_' then we shouldn't change the vector.
bool isNoChange ( std::string &input );
void toLowerCase( std::string &input );

#endif
