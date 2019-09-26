#pragma once
#include <qdatetime.h>
#include <qjsonobject.h>

#include "QJson/AbstractQJsonObjectDeserializer.h"

class TwitterTweetData final : public AbstractQJsonObjectDeserializer
{
    quint64 tweetId = 0;

    QString tweetAuthor;

    QString tweetMessage;

    QString tweetTrainLine;

    QDateTime tweetTimestamp;

public:
    /**
     * \brief Get the tweet message id.
     * \return The tweet message id.
     */
    quint64 getTweetId() const;

    /**
     * \brief Get the tweet message author.
     * \return The tweet message author.
     */
    const QString &getTweetAuthor() const;

    /**
     * \brief Get the tweet message.
     * \return The tweet message.
     */
    const QString &getTweetMessage() const;

    /**
     * \brief Get the tweet message incident train line.
     * \return The tweet message incident train line.
     */
    const QString &getTweetTrainLine() const;

    /**
     * \brief Get the tweet message timestamp.
     * \return The tweet message timestamp.
     */
    const QDateTime &getTweetTimestamp() const;

    /**
     * \brief Deserialize the TwitterTweetData object from a json object.
     * \param json QJsonObject for deserializing TwitterTweetData object.
     */
    void deserialize(const QJsonObject &json) override;
};
