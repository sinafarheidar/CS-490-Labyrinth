#include <iostream>
using namespace std;

class PathKey
{
  private:
    static PathKey* instancePtr; //creates a pointer that points to the instance
    string path = "n/a"; //contains the path 

    public:
        //
        static PathKey* getInstance()
        {
            if(instancePtr == NULL)
            {
              instancePtr = new PathKey();
            }
            
            return instancePtr;
        }

        string getPath()
        {
            return path;
        }
};