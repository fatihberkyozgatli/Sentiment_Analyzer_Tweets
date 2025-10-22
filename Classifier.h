#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <map>
#include "DSString.h"
#include "Tokenizer.h"
#include "FileProcessor.h"

class Classifier
{
public:
    Classifier();  // Constructor
    ~Classifier(); // Destructor

    // Train the classifier with positive and negative tweets
    void train(std::vector<DSString> positiveTweets, std::vector<DSString> negativeTweets);

    // Classify a single tweet as positive or negative
    int classifyTweet(const DSString &tweet);

    // Predict sentiment for a test dataset and save the results
    void predict(const char *testDataFile, const char *outputFile);

    // Calculate accuracy by comparing predicted and actual sentiments
    void calculateAccuracy(const char *testSentimentFile, const char *resultsFile, const char *accuracyFile);

private:
    // Maps to store word counts for positive and negative sentiments
    std::map<DSString, int> positiveWordCounts;
    std::map<DSString, int> negativeWordCounts;
};

#endif // CLASSIFIER_H
