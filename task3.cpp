#include <iostream>
#include <fstream>
#include <string>

void compressFile(const std::string &inputFileName, const std::string &outputFileName)
{
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening input file: " << inputFileName << std::endl;
        return;
    }
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening output file: " << outputFileName << std::endl;
        return;
    }

    char currentChar, nextChar;
    int count;

    while (inputFile.get(currentChar))
    {
        count = 1;
        while (inputFile.get(nextChar) && nextChar == currentChar)
        {
            count++;
        }
        inputFile.unget();

        outputFile << currentChar << count;
    }

    inputFile.close();
    outputFile.close();
    std::cout << "File compressed successfully." << std::endl;
}

void decompressFile(const std::string &inputFileName, const std::string &outputFileName)
{
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening input file: " << inputFileName << std::endl;
        return;
    }
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening output file: " << outputFileName << std::endl;
        return;
    }

    char currentChar;
    int count;

    while (inputFile.get(currentChar))
    {
        if (!(inputFile >> count))
        {
            std::cerr << "Error reading count from file." << std::endl;
            return;
        }

        for (int i = 0; i < count; ++i)
        {
            outputFile.put(currentChar);
        }
    }

    inputFile.close();
    outputFile.close();
    std::cout << "File decompressed successfully." << std::endl;
}

int main()
{
    std::string inputFileName, outputFileName;
    int choice;

    std::cout << "Choose an option:\n1. Compress\n2. Decompress\n";
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1)
    {
        std::cout << "Enter input file name: ";
        std::getline(std::cin, inputFileName);
        std::cout << "Enter output file name: ";
        std::getline(std::cin, outputFileName);
        compressFile(inputFileName, outputFileName);
    }
    else if (choice == 2)
    {
        std::cout << "Enter input file name: ";
        std::getline(std::cin, inputFileName);
        std::cout << "Enter output file name: ";
        std::getline(std::cin, outputFileName);
        decompressFile(inputFileName, outputFileName);
    }
    else
    {
        std::cerr << "Invalid choice." << std::endl;
    }

    return 0;
}
