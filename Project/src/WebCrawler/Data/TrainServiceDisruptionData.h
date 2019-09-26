#pragma once
#include <qdatetime.h>
#include <qjsonobject.h>
#include <qstring.h>
#include <qvector.h>

#include "QJson/AbstractQJsonObjectDeserializer.h"

/**
 * \brief Class containing Google Sheet train service disruption data.
 */
class TrainServiceDisruptionData final : public AbstractQJsonObjectDeserializer
{
    QString incident;

    QString description;

    QDateTime started;

    QDateTime ended;

    QString direction;

    QString line;

    QString trainOperator;

    QString category;

    qint32 duration = 0;

    QDateTime startDate;

    QVector<QString> urls;

public:
    /**
     * \brief Get a short description of the train service incident.
     * \return A short description of the train service incident.
     */
    const QString &getIncident() const;

    /**
     * \brief Get a brief description of the train service incident.
     * \return A brief description of the train service incident.
     */
    const QString &getDescription() const;

    /**
     * \brief Get the date and time when the train service disruption begin.
     * \return The date and time when the train service disruption begin.
     */
    const QDateTime &getStarted() const;

    /**
     * \brief Get the date and time when the train service disruption ends.
     * \return The date and time when the train service disruption ends.
     */
    const QDateTime &getEnded() const;

    /**
     * \brief Get the direction of the train service.
     * \return The direction of the train service.
     */
    const QString &getDirection() const;

    /**
     * \brief Get the train line of the train service.
     * \return The train line of the train service.
     */
    const QString &getLine() const;

    /**
     * \brief Get the train operator of the train service.
     * \return The train operator of the train service.
     */
    const QString &getTrainOperator() const;

    /**
     * \brief Get the category of the train incident.
     * \return The category of the train incident.
     */
    const QString &getCategory() const;

    /**
     * \brief Get the duration of the train disruption in minutes.
     * \return The duration of the train disruption in minutes.
     */
    qint32 getDuration() const;

    /**
     * \brief Get the date when the train disruption happened.
     * \return The date when the train disruption happened.
     */
    const QDateTime &getStartDate() const;

    /**
     * \brief Get the array of urls that covers the article of this incident.
     * \return The array of urls that covers the article of this incident.
     */
    const QVector<QString> &getUrls() const;

    /**
     * \brief Deserialize the TrainServiceDisruptionData object from a json object.
     * \param json QJsonObject for deserializing TrainServiceDisruptionData object.
     */
    void deserialize(const QJsonObject &json) override;
};
