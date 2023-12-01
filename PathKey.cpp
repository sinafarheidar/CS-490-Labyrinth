#include "PathKey.h"
#include <stdlib.h>
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/prepared_statement.h"
using namespace std;

PathKey::PathKey()
{
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
            // Offset = 48
            // Range = 122
            //gives us the ASCII value of all alphanumeric characters (A-Z, a-z)
            //and some special characters
            random = (48 + (rand() % 74)) -'\0'; //converts the number to char
            gate = gate + random;
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

void PathKey::UpdateDatabase()
{
    sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::PreparedStatement *pstmt;

    const string server = "localhost";
    const string username = "root";
    const string password = "root";


	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	//con->setSchema("CS490");

    PathKey p;
    string toInsert = p.getPath();

	pstmt = con->prepareStatement("INSERT INTO KeyTable(pathKeys) VALUES(?)");
	pstmt->setString(1, toInsert);
	pstmt->execute();
	cout << "New key inserted." << endl;

	delete pstmt;
	delete con;
	system("pause");
};
