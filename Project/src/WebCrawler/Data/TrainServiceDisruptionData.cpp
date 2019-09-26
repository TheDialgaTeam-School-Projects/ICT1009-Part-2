#include "TrainServiceDisruptionData.h"

#include <qjsonarray.h>

// ReSharper disable CppUseAuto

const QString &TrainServiceDisruptionData::getIncident() const
{
    return incident;
}

const QString &TrainServiceDisruptionData::getDescription() const
{
    return description;
}

const QDateTime &TrainServiceDisruptionData::getStarted() const
{
    return started;
}

const QDateTime &TrainServiceDisruptionData::getEnded() const
{
    return ended;
}

const QString &TrainServiceDisruptionData::getDirection() const
{
    return direction;
}

const QString &TrainServiceDisruptionData::getLine() const
{
    return line;
}

const QString &TrainServiceDisruptionData::getTrainOperator() const
{
    return trainOperator;
}

const QString &TrainServiceDisruptionData::getCategory() const
{
    return category;
}

qint32 TrainServiceDisruptionData::getDuration() const
{
    return duration;
}

const QDateTime &TrainServiceDisruptionData::getStartDate() const
{
    return startDate;
}

const QVector<QString> &TrainServiceDisruptionData::getUrls() const
{
    return urls;
}

void TrainServiceDisruptionData::deserialize(const QJsonObject &json)
{
    const QString dateTimeFormat = "MMM d, yyyy h:mm:ss AP";

    if (json.contains("incident") && json["incident"].isString())
        this->incident = json["incident"].toString();

    if (json.contains("description") && json["description"].isString())
        this->description = json["description"].toString();

    if (json.contains("started") && json["started"].isString())
        this->started = QDateTime::fromString(json["started"].toString(), dateTimeFormat);

    if (json.contains("ended") && json["ended"].isString())
        this->ended = QDateTime::fromString(json["ended"].toString(), dateTimeFormat);

    if (json.contains("direction") && json["direction"].isString())
        this->direction = json["direction"].toString();

    if (json.contains("line") && json["line"].isString())
        this->line = json["line"].toString();

    if (json.contains("operator") && json["operator"].isString())
        this->trainOperator = json["operator"].toString();

    if (json.contains("category") && json["category"].isString())
        this->category = json["category"].toString();

    if (json.contains("duration") && json["duration"].isDouble())
        this->duration = json["duration"].toInt();

    if (json.contains("startDate") && json["startDate"].isString())
        this->startDate = QDateTime::fromString(json["startDate"].toString(), dateTimeFormat);

    if (json.contains("urls") && json["urls"].isArray())
    {
        QJsonArray urls = json["urls"].toArray();

        for (const QJsonValueRef &url : urls)
            this->urls.append(url.toString());
    }
}
