#include <iostream>
using namespace std;

class PathKey
{
    private:
        string path; //contains the path
    public:
        PathKey();
        void PrintKey();
        string getPath() const {
            return path;
        }
        
};
