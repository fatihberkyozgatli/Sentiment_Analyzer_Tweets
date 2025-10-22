// FileProcessor.h
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <fstream>
#include <vector>
#include "DSString.h"

class FileProcessor
{
public:
    FileProcessor();
    ~FileProcessor();

    // Opens a file for reading
    bool openFileForRead(const DSString &filename);

    // Opens a file for writing
    bool openFileForWrite(const DSString &filename);

    // Reads a line from the file into a DSString object
    bool readLine(DSString &line);

    // Writes a line to the file from a DSString object
    bool writeLine(const DSString &line);

    // Closes the file
    void closeFile();

private:
    std::ifstream inputFile;
    std::ofstream outputFile;
};

#endif // FILEPROCESSOR_H
