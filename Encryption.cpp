#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cstdlib>
#include <string>
#include "PathKey.cpp"
#include "PathKey.h"


using namespace std;
// Function to generate a random matrix as a lattice basis
vector<vector<int>> generateKey(int n){
    vector<vector<int>> key(n, vector<int>(n));

    //random number generation
    srand(time(0));
    for (int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            key[i][j] = rand() %2;
        }
    }
    return key;
}

vector<int> encrypt(const string& message, const vector<vector<int>>& key) {
    vector<int> encryptedVector;

    // Convert the string of numbers to a vector
    for (char ch : message) {
        encryptedVector.push_back(ch - '0');
    }

    // Ensure the key size matches the message size
    if (key.size() != encryptedVector.size()) {
        throw invalid_argument("Key size must match message size");
    }

    // Encrypt by multiplying the key matrix with the message vector
    for (int i = 0; i < key.size(); ++i) {
        int sum = 0;
        for (int j = 0; j < key[i].size(); ++j) {
            sum += key[i][j] * encryptedVector[j];
        }
        encryptedVector[i] = sum % 2;
    }

    return encryptedVector;
}

// Function to decrypt an encrypted vector using the key
string decrypt(const vector<int>& encryptedVector, const vector<vector<int>>& key) {
    // Decrypt by multiplying the transpose of the key matrix with the encrypted vector
    vector<int> decryptedVector(key.size(), 0);

    for (int i = 0; i < key.size(); ++i) {
        int sum = 0;
        for (int j = 0; j < key[i].size(); ++j) {
            sum += key[j][i] * encryptedVector[j];
        }
        decryptedVector[i] = sum % 2;
    }

    // Convert the vector back to a string of numbers
    string decryptedMessage;
    for (int digit : decryptedVector) {
        decryptedMessage.push_back(digit + '0');
    }

    return decryptedMessage;
}

int main()
{
    PathKey pathKeyObject;

    pathKeyObject.PrintKey();

    string keyAsString = pathKeyObject.getPath();

    int keySize = keyAsString.size();
    vector<vector<int>> secretKey = generateKey(keySize);

    vector<int> encryptedKey = encrypt(keyAsString, secretKey);
    cout<< "Encrypted Key";
    for(int digit : encryptedKey)
    {
        cout<<digit;

    }
    cout <<endl;

    string decryptedKey = decrypt(encryptedKey, secretKey);
    cout << "Decrypted Message: " << decryptedKey << endl;

    return 0;

}