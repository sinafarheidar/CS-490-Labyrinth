#include "PathKey.h"

PathKey::PathKey()
{
    cout << "hello" << endl;

    string key;
    string gate;
    int keySize = 4; //number of key/gate pairs
    int pairLength = 4; //length of key/gates
    char random;

    // Providing a seed value
    srand((unsigned) time(NULL));

    //for loop based on keySize (which we can change later)
    for(int i=1; i<=keySize; i++)
    {
        // Loop to generate gates
        for(int i=1; i<=pairLength; i++)
        {
            // Retrieve a random number between 65 and 122
            // Offset = 65
            // Range = 122
            //gives us the ASCII value of all alphanumeric characters (A-Z, a-z)
            //and some special characters
            random = (48 + (rand() % 74)) -'\0';
            gate = gate + random; //converts the number to char
        }

        gate = gate + '-'; //adds a seperator between gates/keys

        // Loop to generate keys
        for(int i=1; i<=pairLength; i++)
        {
            random = (48 + (rand() % 74)) -'\0';
            key = key + random;
        }
        
        key = key + '-'; //adds a seperator between gates/keys

        path = path + (gate + key); //adds the gate/key pair to the path
        key = ""; //clears key for next loop
        gate = ""; //clears gate for next loop
    }

    path.pop_back(); //removes last '-'
};

void PathKey::PrintKey()
{
    cout << "The key is: " << path << endl;
};
