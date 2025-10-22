#include "FileProcessor.h"

FileProcessor::FileProcessor()
{
    // Constructor
}

FileProcessor::~FileProcessor()
{
    // Destructor
    closeFile();
}

bool FileProcessor::openFileForRead(const DSString &filename)
{
    inputFile.open(filename.c_str());
    return inputFile.is_open();
}

bool FileProcessor::openFileForWrite(const DSString &filename)
{
    outputFile.open(filename.c_str());
    return outputFile.is_open();
}

bool FileProcessor::readLine(DSString &line)
{
    if (inputFile.is_open() && !inputFile.eof())
    {
        std::string stdLine;
        std::getline(inputFile, stdLine);
        line = DSString(stdLine.c_str());
        return true;
    }
    return false;
}

bool FileProcessor::writeLine(const DSString &line)
{
    if (outputFile.is_open())
    {
        outputFile << line.c_str() << std::endl;
        return true;
    }
    return false;
}

void FileProcessor::closeFile()
{
    if (inputFile.is_open())
    {
        inputFile.close();
    }
    if (outputFile.is_open())
    {
        outputFile.close();
    }
}
