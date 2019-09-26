#include "dataCounts.h"

// ReSharper disable CppUseAuto

QVector<int> dataCounts::getGSCountLines(QVector<TrainServiceDisruptionData> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i).getLine().toStdString() == "North-South Line")
        {
            nsl += 1;
        }
        else if (data.at(i).getLine().toStdString() == "East-West Line")
        {
            ewl += 1;
        }
        else if (data.at(i).getLine().toStdString() == "North-East Line")
        {
            nel += 1;
        }
        else if (data.at(i).getLine().toStdString() == "Circle Line")
        {
            ccl += 1;
        }
        else if (data.at(i).getLine().toStdString() == "Downtown Line")
        {
            dtl += 1;
        }
        else
        {
            orl += 1;
        }
    }

    QVector<int> counts;
    counts.append(nsl);
    counts.append(ewl);
    counts.append(nel);
    counts.append(ccl);
    counts.append(dtl);
    counts.append(orl);

    return counts;
}

QVector<int> dataCounts::getYear(QVector<TrainServiceDisruptionData> &data, QString year)
{
    for (int i = 0; i < data.size(); i++)
    {
        QString dataYear = QString::number(data.at(i).getStartDate().date().year());

        if (dataYear == year)
        {
            if (data.at(i).getDuration() < 30)
            {
                less30 += 1;
            }
            else if (data.at(i).getDuration() > 30 && data.at(i).getDuration() < 60)
            {
                less1h += 1;
            }
            else if (data.at(i).getDuration() > 60 && data.at(i).getDuration() < 120)
            {
                less2h += 1;
            }
            else if (data.at(i).getDuration() > 120)
            {
                more2h += 1;
            }
        }
    }

    QVector<int> countDuration;
    countDuration.append(less30);
    countDuration.append(less1h);
    countDuration.append(less2h);
    countDuration.append(more2h);

    return countDuration;
}

QVector<int> dataCounts::getTDCountLines(QVector<TwitterTweetData> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i).getTweetTrainLine().toStdString() == "North-South Line")
        {
            nsl += 1;
        }
        else if (data.at(i).getTweetTrainLine().toStdString() == "East-West Line")
        {
            ewl += 1;
        }
        else if (data.at(i).getTweetTrainLine().toStdString() == "North-East Line")
        {
            nel += 1;
        }
        else if (data.at(i).getTweetTrainLine().toStdString() == "Circle Line")
        {
            ccl += 1;
        }
        else if (data.at(i).getTweetTrainLine().toStdString() == "Downtown Line")
        {
            dtl += 1;
        }
        else
        {
            orl += 1;
        }
    }

    QVector<int> counts;
    counts.append(nsl);
    counts.append(ewl);
    counts.append(nel);
    counts.append(ccl);
    counts.append(dtl);
    counts.append(orl);

    return counts;
}

QVector<int> dataCounts::getMonthCount(QVector<TwitterTweetData> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i).getTweetTimestamp().date().month() == 1)
        {
            jan += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 2)
        {
            feb += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 3)
        {
            mar += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 4)
        {
            apr += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 5)
        {
            jun += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 6)
        {
            jul += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 7)
        {
            aug += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 8)
        {
            oct += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 9)
        {
            sep += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 10)
        {
            sep += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 11)
        {
            nov += 1;
        }
        else if (data.at(i).getTweetTimestamp().date().month() == 12)
        {
            dec += 1;
        }
    }

    QVector<int> counts;
    counts.append(jan);
    counts.append(feb);
    counts.append(mar);
    counts.append(apr);
    counts.append(may);
    counts.append(jun);
    counts.append(jul);
    counts.append(aug);
    counts.append(oct);
    counts.append(sep);
    counts.append(nov);
    counts.append(dec);

    return counts;
}
