#pragma once
#include <qvector.h>
#include "src/WebCrawler/Data/TrainServiceDisruptionData.h"
#include "src/WebCrawler/Data/TwitterTweetData.h"

class dataCounts {
	//Google Sheet Lines Count Variables
	int nsl = 0;
	int ewl = 0;
	int nel = 0;
	int ccl = 0;
	int dtl = 0;
	int orl = 0;
	int year = 0;

	//Google Sheet Duration Count Variables
	int less30 = 0, less1h = 0, less2h = 0, more2h = 0;

	//Twitter Month Count Variables
	int jan = 0;
	int feb = 0;
	int mar = 0;
	int apr = 0;
	int may = 0;
	int jun = 0;
	int jul = 0;
	int aug = 0;
	int sep = 0;
	int oct = 0;
	int nov = 0;
	int dec = 0;

	public:
		QVector<int> getGSCountLines(QVector<TrainServiceDisruptionData> &data);
		QVector<int> getYear(QVector<TrainServiceDisruptionData> &data, QString year);
		QVector<int> getTDCountLines(QVector<TwitterTweetData> &data);
		QVector<int> getMonthCount(QVector<TwitterTweetData> &data);
};