#include "TwitterTweetsSearchExtractor.h"

TwitterTweetData TwitterTweetsSearchExtractor::deserialize(const QJsonObject &json)
{
    TwitterTweetData data;
    data.deserialize(json);

    return data;
}

TwitterTweetsSearchExtractor::TwitterTweetsSearchExtractor()
{
    cacheFileLocation = "TwitterSearchData.json";
    commandLine = "TwitterTweetsSearchExtractor";
}
