#include "TrainServiceDisruptionSheetExtractor.h"

TrainServiceDisruptionData TrainServiceDisruptionSheetExtractor::deserialize(const QJsonObject &json)
{
    TrainServiceDisruptionData data;
    data.deserialize(json);

    return data;
}

TrainServiceDisruptionSheetExtractor::TrainServiceDisruptionSheetExtractor()
{
    cacheFileLocation = "TrainServiceDisruptionSheet.json";
    commandLine = "TrainServiceDisruptionSheetExtractor";
}
