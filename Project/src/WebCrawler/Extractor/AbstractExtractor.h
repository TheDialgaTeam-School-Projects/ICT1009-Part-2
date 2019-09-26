#pragma once
#include <qfile.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qtextstream.h>
#include <qvector.h>
#include <sstream>

using std::stringstream;

// ReSharper disable CppUseAuto

/**
 * \brief Abstract class for extractor to get data.
 * \tparam TData Data type.
 */
template <class TData>
class AbstractExtractor
{
protected:
    QString cacheFileLocation;
    QString commandLine;

    virtual TData deserialize(const QJsonObject &json) = 0;

public:
    AbstractExtractor() = default;
    virtual ~AbstractExtractor() = default;

    QVector<TData> getData();
    QVector<TData> getData(bool ignoreCache);

    AbstractExtractor(const AbstractExtractor &) = default;
    AbstractExtractor &operator=(const AbstractExtractor &) = default;
    AbstractExtractor(AbstractExtractor &&) = default;
    AbstractExtractor &operator=(AbstractExtractor &&) = default;
};

template <class TData>
QVector<TData> AbstractExtractor<TData>::getData()
{
    return getData(false);
}

template <class TData>
QVector<TData> AbstractExtractor<TData>::getData(const bool ignoreCache)
{
    if (ignoreCache)
    {
        stringstream stringStream;

        if (QFile::exists("Resources/gson-2.8.5.jar") && QFile::exists("Resources/jsoup-1.11.3.jar"))
            stringStream << "cd Resources && java -cp .;gson-2.8.5.jar;jsoup-1.11.3.jar webcrawler.Main " << commandLine.toStdString();
        else if (QFile::exists("gson-2.8.5.jar") && QFile::exists("jsoup-1.11.3.jar"))
            stringStream << "java -cp .;gson-2.8.5.jar;jsoup-1.11.3.jar webcrawler.Main " << commandLine.toStdString();

        system(stringStream.str().c_str());
    }

    QVector<TData> result;

    QString cacheFilePath = cacheFileLocation;

    if (QFile::exists("Resources/" + cacheFileLocation))
        cacheFilePath = "Resources/" + cacheFileLocation;

    if (!QFile::exists(cacheFilePath))
        return result;

    // File exists. Read this json file.
    QFile file(cacheFilePath);

    // Could not deserialize the file.
    if (!file.open(QIODevice::ReadOnly))
        return result;

    QTextStream json(&file);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(json.readAll().toUtf8());

    if (jsonDocument.isArray())
    {
        for (QJsonValueRef &jsonValueRef : jsonDocument.array())
        {
            if (jsonValueRef.isObject())
                result.append(deserialize(jsonValueRef.toObject()));
        }
    }

    file.close();

    return result;
}
