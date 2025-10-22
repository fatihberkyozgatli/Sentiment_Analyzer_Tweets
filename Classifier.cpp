#include "Classifier.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include "./stemming/src/english_stem.h" // Include Oleander Stemming Library
#include <iomanip>                       // for std::setprecision

Classifier::Classifier()
{
    // Constructor
}

Classifier::~Classifier()
{
    // Destructor
}

void Classifier::train(std::vector<DSString> positiveTweets, std::vector<DSString> negativeTweets)
{
    Tokenizer tokenizer;
    stemming::english_stem<> StemEnglish; // Initialize the stemmer

    // Create a vector with 'Stop Words'
    std::vector<DSString> stopWords;
    std::fstream stopWordsFile;
    stopWordsFile.open("./stopwords.csv");
    std::string word;
    while (getline(stopWordsFile, word))
    {
        stopWords.push_back(DSString(word.c_str()));
    }
    stopWordsFile.close();

    // Process positive tweets
    for (const auto &tweet : positiveTweets)
    {
        auto tokens = tokenizer.tokenizeTweet(tweet);
        for (const auto &token : tokens)
        {
            std::string strToken = token.c_str();                     // Convert to std::string
            std::wstring wstrToken(strToken.begin(), strToken.end()); // Convert to std::wstring
            StemEnglish(wstrToken);                                   // Stem the token
            strToken.assign(wstrToken.begin(), wstrToken.end());      // Convert back to std::string
            DSString lowerToken(strToken.c_str());                    // Convert to DSString
            lowerToken = lowerToken.toLower();                        // Convert to lowercase

            // Check if the token is not a stop word before counting
            if (std::find(stopWords.begin(), stopWords.end(), lowerToken) == stopWords.end())
            {
                positiveWordCounts[lowerToken]++;
            }
        }
    }

    // Process negative tweets
    for (const auto &tweet : negativeTweets)
    {
        auto tokens = tokenizer.tokenizeTweet(tweet);
        for (const auto &token : tokens)
        {
            std::string strToken = token.c_str();                     // Convert to std::string
            std::wstring wstrToken(strToken.begin(), strToken.end()); // Convert to std::wstring
            StemEnglish(wstrToken);                                   // Stem the token
            strToken.assign(wstrToken.begin(), wstrToken.end());      // Convert back to std::string
            DSString lowerToken(strToken.c_str());                    // Convert to DSString
            lowerToken = lowerToken.toLower();                        // Convert to lowercase

            // Check if the token is not a stop word before counting
            if (std::find(stopWords.begin(), stopWords.end(), lowerToken) == stopWords.end())
            {
                negativeWordCounts[lowerToken]++;
            }
        }
    }
}

int Classifier::classifyTweet(const DSString &tweet)
{
    Tokenizer tokenizer;
    stemming::english_stem<> StemEnglish; // Initialize the stemmer
    int positiveCount = 0;
    int negativeCount = 0;

    auto tokens = tokenizer.tokenizeTweet(tweet);
    for (const auto &token : tokens)
    {
        std::string strToken = token.c_str();                     // Convert to std::string
        std::wstring wstrToken(strToken.begin(), strToken.end()); // Convert to std::wstring
        StemEnglish(wstrToken);                                   // Stem the token
        strToken.assign(wstrToken.begin(), wstrToken.end());      // Convert back to std::string
        DSString lowerToken(strToken.c_str());                    // Convert to DSString
        lowerToken = lowerToken.toLower();                        // Convert to lowercase

        // Count the positive and negative word occurrences
        positiveCount += positiveWordCounts[lowerToken];
        negativeCount += negativeWordCounts[lowerToken];
    }

    // Determine sentiment based on word counts
    if (positiveCount > negativeCount)
    {
        return 4; // Positive sentiment
    }
    else
    {
        return 0; // Negative sentiment
    }
}

void Classifier::predict(const char *testDataFile, const char *outputFile)
{
    FileProcessor fileProcessor;
    DSString line;

    if (!fileProcessor.openFileForRead(testDataFile))
    {
        std::cerr << "Could not open test data file for reading." << std::endl;
        return;
    }

    if (!fileProcessor.openFileForWrite(outputFile))
    {
        std::cerr << "Could not open output file for writing." << std::endl;
        return;
    }

    // Write the header to the output file
    fileProcessor.writeLine(DSString("Sentiment,id"));

    // Skip the header line in the test data file
    fileProcessor.readLine(line);

    while (fileProcessor.readLine(line))
    {
        int commaPos = line.find(',');
        if (commaPos == -1)
            continue; // Skip if the format is incorrect

        DSString id = line.substring(0, commaPos);
        DSString tweet = line.substring(commaPos + 1, line.length() - commaPos - 1);

        int sentiment = classifyTweet(tweet);

        // Format the output as "Sentiment,id"
        DSString outputLine = DSString(std::to_string(sentiment).c_str()) + DSString(",") + id;

        fileProcessor.writeLine(outputLine);
    }

    fileProcessor.closeFile();
}

void Classifier::calculateAccuracy(const char *testSentimentFile, const char *resultsFile, const char *accuracyFile)
{
    std::ifstream testFileStream(testSentimentFile), resultsFileStream(resultsFile);
    std::ofstream accuracyFileStream(accuracyFile);
    if (!testFileStream.is_open() || !resultsFileStream.is_open() || !accuracyFileStream.is_open())
    {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    std::string testLine, resultsLine;
    int correctCount = 0, totalCount = 0;
    std::stringstream buffer;

    // Skip headers
    std::getline(testFileStream, testLine);
    std::getline(resultsFileStream, resultsLine);

    while (std::getline(testFileStream, testLine) && std::getline(resultsFileStream, resultsLine))
    {
        std::stringstream testSS(testLine), resultsSS(resultsLine);
        std::string testSentiment, resultsSentiment, testId, resultsId;

        std::getline(testSS, testSentiment, ',');
        std::getline(testSS, testId, ',');

        std::getline(resultsSS, resultsSentiment, ',');
        std::getline(resultsSS, resultsId, ',');

        // Increment the total count
        totalCount++;

        if (testSentiment == resultsSentiment)
        {
            // Increment the correct count
            correctCount++;
        }
        else
        {
            // Log the incorrect classification to the buffer
            buffer << "Predicted: " << resultsSentiment << ", Actual: " << testSentiment << ", ID: " << testId << std::endl;
        }
    }

    double accuracy = (double)correctCount / totalCount * 100;

    // Write the accuracy to the file
    accuracyFileStream << "Accuracy: " << std::fixed << std::setprecision(2) << accuracy << "%" << std::endl;
    if (accuracyFileStream.fail())
    {
        std::cerr << "Failed to write to file." << std::endl;
    }

    // Then write the buffer content (incorrect classifications)
    accuracyFileStream << buffer.str();

    testFileStream.close();
    resultsFileStream.close();
    accuracyFileStream.close();
}
