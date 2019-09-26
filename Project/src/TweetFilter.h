#pragma once
#include "src/WebCrawler/Extractor/TwitterTweetsSearchExtractor.h"

/**
 * \brief Class that removes irrelevant information from information extracted in twitter
 */
class TweetFilter
{
	QVector<TwitterTweetData> filteredTweets;

public:
	void filter();
	QVector<TwitterTweetData> &getTweets();
};

