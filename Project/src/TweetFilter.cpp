#include "TweetFilter.h"

#include <vector>
#include <QRegularExpression>
#include <QString>

#include "src/WebCrawler/Extractor/TwitterTweetsSearchExtractor.h"

// ReSharper disable CppUseAuto

void TweetFilter::filter()
{
	// check if data is filtered
    if (!filteredTweets.isEmpty())
        return;

    TwitterTweetsSearchExtractor extractor;
    QVector<TwitterTweetData> tweets = extractor.getData();

    std::vector<QRegularExpression> pattern;

    // find keywords from tweets
	QRegularExpression re("(?=.*[Dd]elay).*");
    pattern.push_back(re);
    re.setPattern("(?=.*[Ff]ault).*");
    pattern.push_back(re);
    re.setPattern("(?=.*[Aa]ccident).*");
    pattern.push_back(re);

	// compare tweets by date and train line to remove repeated tweets, 
	// assume no multiple train breakdowns of the same line on the same day
    QDate prevDate = tweets[0].getTweetTimestamp().date();
    bool NSLflag = false, EWLflag = false, NELflag = false, CCLflag = false, DTLflag = false, BPLRTflag = false;

    std::reverse(tweets.begin(), tweets.end());
    
    for (TwitterTweetData &tweet : tweets)
    {
        QDate currDate = tweet.getTweetTimestamp().date();

        // reset flag if date changes
		if (prevDate != currDate)
        {
            NSLflag = false;
            EWLflag = false;
            NELflag = false;
            CCLflag = false;
            DTLflag = false;
            BPLRTflag = false;
            prevDate = currDate;
        }

        for (int i = 0; i < pattern.size(); i++)
        {
            QRegularExpressionMatch match = pattern[i].match(tweet.getTweetMessage());
			
			// update filteredTweets when tweet message matches keyword, and train breakdown data are not the same trainLine on the same day 
            if (match.hasMatch())
            {
                QString line = tweet.getTweetTrainLine();

                if (line == "North-South Line" && !NSLflag)
                {
                    filteredTweets.append(tweet);
                    NSLflag = true;
                }
                else if (line == "East-West Line" && !EWLflag)
                {
                    filteredTweets.append(tweet);
                    EWLflag = true;
                }
                else if (line == "North-East Line" && !NELflag)
                {
                    filteredTweets.append(tweet);
                    NELflag = true;
                }
                else if (line == "Circle Line" && !CCLflag)
                {
                    filteredTweets.append(tweet);
                    CCLflag = true;
                }
                else if (line == "Downtown Line" && !DTLflag)
                {
                    filteredTweets.append(tweet);
                    DTLflag = true;
                }
                else if (line == "Bukit Panjang LRT" && !BPLRTflag)
                {
                    filteredTweets.append(tweet);
                    BPLRTflag = true;
                }
                break;
            }
        }
    }
}

QVector<TwitterTweetData> &TweetFilter::getTweets()
{
    return filteredTweets;
}
