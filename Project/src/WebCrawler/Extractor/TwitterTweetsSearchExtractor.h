#pragma once
#include "AbstractExtractor.h"
#include "src/WebCrawler/Data/TwitterTweetData.h"

/**
 * \brief Class that extract information about train service disruption in twitter.
 */
class TwitterTweetsSearchExtractor final : public AbstractExtractor<TwitterTweetData>
{
protected:
    TwitterTweetData deserialize(const QJsonObject &json) override;

public:
    TwitterTweetsSearchExtractor();
};
