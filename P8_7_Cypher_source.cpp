/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 	CSC 242
** Assignment: 	Lesson # 5
** File: 	source.cpp
** Description: Assignment 5: Comprehensive Program Challenge (Signature Assignment)
**
** Author: 	John Paul Shaner
** Date: 	08/14/2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;


// Team Member: John Paul Shaner
// Creates the cipher alphabet using the supplied keyword.
string buildCipherAlphabet(const string& keyword)
{
    string cipher = "";

    // Add each unique letter from the keyword.
    for (int i = 0; i < keyword.length(); i++)
    {
        char letter = toupper(keyword[i]);

        // Only use alphabetic characters.
        if (isalpha(letter))
        {
            // Add the letter only if it has not already been added.
            if (cipher.find(letter) == string::npos)
            {
                cipher += letter;
            }
        }
    }

    // Add remaining letters in reverse alphabetical order.
    for (char letter = 'Z'; letter >= 'A'; letter--)
    {
        if (cipher.find(letter) == string::npos)
        {
            cipher += letter;
        }
    }

    return cipher;
}


// Team Member: John Paul Shaner
// Encrypts a single character using the cipher alphabet.
char encryptCharacter(char ch, const string& cipher)
{
    // Leave spaces, numbers, and punctuation unchanged.
    if (!isalpha(ch))
    {
        return ch;
    }

    bool wasLowercase = islower(ch);

    // Convert character to uppercase for processing.
    char upperCharacter = toupper(ch);

    // Determine the character's position in the normal alphabet.
    int position = upperCharacter - 'A';

    // Use the same position in the cipher alphabet.
    char encryptedCharacter = cipher[position];

    // Preserve lowercase letters.
    if (wasLowercase)
    {
        encryptedCharacter = tolower(encryptedCharacter);
    }

    return encryptedCharacter;
}


// Team Member: John Paul Shaner
// Decrypts a single character using the cipher alphabet.
char decryptCharacter(char ch, const string& cipher)
{
    // Leave spaces, numbers, and punctuation unchanged.
    if (!isalpha(ch))
    {
        return ch;
    }

    bool wasLowercase = islower(ch);

    // Convert character to uppercase for processing.
    char upperCharacter = toupper(ch);

    // Locate the encrypted character in the cipher alphabet.
    size_t position = cipher.find(upperCharacter);

    // Convert its position back to the normal alphabet.
    char decryptedCharacter = 'A' + position;

    // Preserve lowercase letters.
    if (wasLowercase)
    {
        decryptedCharacter = tolower(decryptedCharacter);
    }

    return decryptedCharacter;
}


// Team Member: John Paul Shaner
// Reads an input file and encrypts or decrypts its contents.
bool processFile(const string& inputFileName,
    const string& outputFileName,
    const string& cipher,
    bool decrypt)
{
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    // Verify that the input file opened correctly.
    if (!inputFile)
    {
        cout << "Error: Unable to open input file." << endl;
        return false;
    }

    // Verify that the output file opened correctly.
    if (!outputFile)
    {
        cout << "Error: Unable to open output file." << endl;
        return false;
    }

    char ch;

    // Read and process the file one character at a time.
    while (inputFile.get(ch))
    {
        if (decrypt)
        {
            ch = decryptCharacter(ch, cipher);
        }
        else
        {
            ch = encryptCharacter(ch, cipher);
        }

        outputFile.put(ch);
    }

    inputFile.close();
    outputFile.close();

    return true;
}


// Team Member: John Paul Shaner
// Controls the program and processes command-line arguments.
int main(int argc, char* argv[])
{
    bool decrypt = false;

    string keyword;
    string inputFileName;
    string outputFileName;

    /*
        Encryption example:
        crypt -kPINEAPPLE input.txt encrypted.txt

        Decryption example:
        crypt -d -kPINEAPPLE encrypted.txt decrypted.txt
    */

    // Encryption requires four command-line arguments.
    if (argc == 4)
    {
        string keyArgument = argv[1];

        // Make sure a keyword was supplied.
        if (keyArgument.substr(0, 2) != "-k")
        {
            cout << "Error: A keyword must be supplied." << endl;
            return 1;
        }

        keyword = keyArgument.substr(2);
        inputFileName = argv[2];
        outputFileName = argv[3];
    }

    // Decryption requires five command-line arguments.
    else if (argc == 5)
    {
        string option = argv[1];
        string keyArgument = argv[2];

        if (option != "-d")
        {
            cout << "Error: Invalid option." << endl;
            return 1;
        }

        if (keyArgument.substr(0, 2) != "-k")
        {
            cout << "Error: A keyword must be supplied." << endl;
            return 1;
        }

        decrypt = true;
        keyword = keyArgument.substr(2);
        inputFileName = argv[3];
        outputFileName = argv[4];
    }

    else
    {
        cout << "Usage for encryption:" << endl;
        cout << "crypt -kKEYWORD input.txt output.txt" << endl;

        cout << endl;

        cout << "Usage for decryption:" << endl;
        cout << "crypt -d -kKEYWORD input.txt output.txt" << endl;

        return 1;
    }

    // A blank keyword is not allowed.
    if (keyword.empty())
    {
        cout << "Error: A keyword must be supplied." << endl;
        return 1;
    }

    // Build the cipher alphabet from the keyword.
    string cipher = buildCipherAlphabet(keyword);

    cout << "Keyword: " << keyword << endl;
    cout << "Cipher Alphabet: " << cipher << endl;

    // Encrypt or decrypt the file.
    if (processFile(inputFileName,
        outputFileName,
        cipher,
        decrypt))
    {
        if (decrypt)
        {
            cout << "File decrypted successfully." << endl;
        }
        else
        {
            cout << "File encrypted successfully." << endl;
        }
    }

    return 0;
}