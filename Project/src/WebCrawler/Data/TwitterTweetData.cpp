#include "TwitterTweetData.h"

quint64 TwitterTweetData::getTweetId() const
{
    return tweetId;
}

const QString &TwitterTweetData::getTweetAuthor() const
{
    return tweetAuthor;
}

const QString &TwitterTweetData::getTweetMessage() const
{
    return tweetMessage;
}

const QString &TwitterTweetData::getTweetTrainLine() const
{
    return tweetTrainLine;
}

const QDateTime &TwitterTweetData::getTweetTimestamp() const
{
    return tweetTimestamp;
}

void TwitterTweetData::deserialize(const QJsonObject &json)
{
    const QString dateTimeFormat = "MMM d, yyyy h:mm:ss AP";

    if (json.contains("tweetId") && json["tweetId"].isDouble())
        this->tweetId = static_cast<quint64>(json["tweetId"].toDouble());

    if (json.contains("tweetAuthor") && json["tweetAuthor"].isString())
        this->tweetAuthor = json["tweetAuthor"].toString();

    if (json.contains("tweetMessage") && json["tweetMessage"].isString())
        this->tweetMessage = json["tweetMessage"].toString();

    if (json.contains("tweetTrainLine") && json["tweetTrainLine"].isString())
        this->tweetTrainLine = json["tweetTrainLine"].toString();

    if (json.contains("tweetTimestamp") && json["tweetTimestamp"].isString())
        this->tweetTimestamp = QDateTime::fromString(json["tweetTimestamp"].toString(), dateTimeFormat);
}
