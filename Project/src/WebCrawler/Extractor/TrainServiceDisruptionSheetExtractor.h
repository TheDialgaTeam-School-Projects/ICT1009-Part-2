#pragma once
#include "AbstractExtractor.h"
#include "src/WebCrawler/Data/TrainServiceDisruptionData.h"

/**
 * \brief Class that extract information about train service disruption in google sheets.
 */
class TrainServiceDisruptionSheetExtractor final : public AbstractExtractor<TrainServiceDisruptionData>
{
protected:
    TrainServiceDisruptionData deserialize(const QJsonObject &json) override;

public:
    TrainServiceDisruptionSheetExtractor();
};
