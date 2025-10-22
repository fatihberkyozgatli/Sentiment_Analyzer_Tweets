#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "DSString.h"
#include "Tokenizer.h"
#include "Classifier.h"
#include "FileProcessor.h"

using namespace std;

// Read a CSV line and split it into cells
vector<string> readCSVLine(istream &str)
{
    vector<string> result;
    string line;
    getline(str, line);

    stringstream lineStream(line);
    string cell;

    while (getline(lineStream, cell, ','))
    {
        result.push_back(cell);
    }
    return result;
}

int main(int argc, char *argv[])
{
    // Command-line arguments: input and output file paths
    const char *trainDataFile = argv[1];
    const char *testDataFile = argv[2];
    const char *testSentimentFile = argv[3];
    const char *resultsFile = argv[4];
    const char *accuracyFile = argv[5];

    // Create an instance of the Classifier class
    Classifier myClassifier;

    // Containers to store training and test data
    vector<DSString> positiveTrainTweets, negativeTrainTweets;
    vector<DSString> testTweets;

    // Open training and test data files
    ifstream trainFile(trainDataFile);
    ifstream testFile(testDataFile);

    // Read the header line from the training data file (and ignore it)
    readCSVLine(trainFile);

    // Read each line of training data
    while (trainFile)
    {
        vector<string> row = readCSVLine(trainFile);
        if (row.size() < 6)
        {
            continue; // Skip malformed lines
        }

        DSString sentiment = row[0].c_str();
        DSString tweet = row[5].c_str();

        if (sentiment == "4")
        {
            positiveTrainTweets.push_back(tweet);
        }
        else if (sentiment == "0")
        {
            negativeTrainTweets.push_back(tweet);
        }
    }

    // Train the classifier using the training data
    myClassifier.train(positiveTrainTweets, negativeTrainTweets);

    // Read the header line from the test data file (and ignore it)
    readCSVLine(testFile);

    // Read each line of test data
    while (testFile)
    {
        vector<string> row = readCSVLine(testFile);
        if (row.size() < 6)
        {
            continue; // Skip malformed lines
        }

        DSString tweet = row[5].c_str();
        testTweets.push_back(tweet);
    }

    // Predict sentiment for test data and write results to a file
    myClassifier.predict(testDataFile, resultsFile);

    // Calculate accuracy and write results to an accuracy file
    myClassifier.calculateAccuracy(testSentimentFile, resultsFile, accuracyFile);

    return 0;
}
