#pragma once

/**
 * \brief Abstract class for objects that can be deserialize from a json object.
 */
class AbstractQJsonObjectDeserializer
{
public:
    AbstractQJsonObjectDeserializer() = default;
    virtual ~AbstractQJsonObjectDeserializer() = default;

    /**
     * \brief Deserialize the object from a json object.
     * \param json QJsonObject for deserializing this object.
     */
    virtual void deserialize(const QJsonObject &json) = 0;

    AbstractQJsonObjectDeserializer(const AbstractQJsonObjectDeserializer &) = default;
    AbstractQJsonObjectDeserializer &operator=(const AbstractQJsonObjectDeserializer &) = default;
    AbstractQJsonObjectDeserializer(AbstractQJsonObjectDeserializer &&) = default;
    AbstractQJsonObjectDeserializer &operator=(AbstractQJsonObjectDeserializer &&) = default;
};
