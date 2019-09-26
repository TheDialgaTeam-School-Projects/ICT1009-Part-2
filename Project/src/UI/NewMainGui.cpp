#include "NewMainGui.h"

#include <QBarCategoryAxis>
#include <qchart.h>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QLineSeries>
#include <QPieSeries>
#include <QValueAxis>

#include "src/dataCounts.h"

using QtCharts::QBarCategoryAxis;
using QtCharts::QBarSeries;
using QtCharts::QBarSet;
using QtCharts::QChart;
using QtCharts::QChartView;
using QtCharts::QLineSeries;
using QtCharts::QPieSeries;
using QtCharts::QPieSlice;
using QtCharts::QValueAxis;

// ReSharper disable CppUseAuto

NewMainGui::NewMainGui(QWidget *parent):
    QMainWindow(parent),
    ui()
{
    ui.setupUi(this);
    tweetFilter.filter();

    /*
     * PAGE 0 - Main Menu
     */
    connect(ui.mainMenuStartButton, SIGNAL(released()), this, SLOT(mainMenuButtonReleased()));

    /*
     * PAGE 1 - Google Sheet Main Menu.
     */
    connect(ui.googleSheetMainMenuNextButton, SIGNAL(released()), this, SLOT(googleSheetMainMenuNextButtonReleased()));
    connect(ui.googleSheetMainMenuBackButton, SIGNAL(released()), this, SLOT(googleSheetMainMenuBackButtonReleased()));

    /*
     * PAGE 2 - Google Sheet Sort By Line.
     */
    connect(ui.googleSheetSortByLineBarChartButton, SIGNAL(released()), this, SLOT(googleSheetSortByLineBarChartButtonReleased()));
    connect(ui.googleSheetSortByLinePieChartButton, SIGNAL(released()), this, SLOT(googleSheetSortByLinePieChartButtonReleased()));
    connect(ui.googleSheetSortByLineBackButton, SIGNAL(released()), this, SLOT(googleSheetSortByLineBackButtonReleased()));

    /*
     * PAGE 3 - Google Sheet Sort By Line Charts.
     */
    connect(ui.googleSheetSortByLineChartBackButton, SIGNAL(released()), this, SLOT(googleSheetSortByLineChartBackButtonReleased()));

    /*
     * PAGE 4 - Google Sheet Sort By DateTime.
     */
    connect(ui.googleSheetSortByDateTimeBackButton, SIGNAL(released()), this, SLOT(googleSheetSortByDateTimeBackButtonReleased()));
    connect(ui.googleSheetSortByDateTimeChartButton, SIGNAL(released()), this, SLOT(googleSheetSortByDateTimeChartButtonReleased()));
    connect(ui.googleSheetSortByDateTimeGenerateButton, SIGNAL(released()), this, SLOT(googleSheetSortByDateTimeGenerateButtonReleased()));

    /*
     * PAGE 5 - Google Sheet Sort By DateTime Charts.
     */
    connect(ui.googleSheetSortByDateTimeChartsBackButton, SIGNAL(released()), this, SLOT(googleSheetSortByDateTimeChartsBackButtonReleased()));

    /*
     * PAGE 6 - Twitter Main Menu.
     */
    connect(ui.twitterMainMenuBackButton, SIGNAL(released()), this, SLOT(twitterMainMenuBackButtonReleased()));
    connect(ui.twitterMainMenuSortByTrainLineButton, SIGNAL(released()), this, SLOT(twitterMainMenuSortByTrainLineButtonReleased()));
    connect(ui.twitterMainMenuSortByMonthButton, SIGNAL(released()), this, SLOT(twitterMainMenuSortByMonthButtonReleased()));
    connect(ui.twitterMainMenuGenerateButton, SIGNAL(released()), this, SLOT(twitterMainMenuGenerateButtonReleased()));

    /*
     * PAGE 7 - Twitter Charts.
     */
    connect(ui.twitterChartsBackButton, SIGNAL(released()), this, SLOT(twitterChartsBackButtonReleased()));
}

/*
 * GUI PAGES FUNCTIONS:
 * 0 - Main Menu
 * 1 - Google Sheet Main Menu.
 * 2 - Google Sheet Sort By Line.
 * 3 - Google Sheet Sort By Line Charts.
 * 4 - Google Sheet Sort By DateTime.
 * 5 - Google Sheet Sort By DateTime Charts.
 * 6 - Twitter Main Menu.
 * 7 - Twitter Charts.
 */

void NewMainGui::gotoPage(const int index) const
{
    beforeGotoPage(index);

    ui.stackedWidget->setCurrentIndex(index);

    afterGotoPage(index);
}

void NewMainGui::beforeGotoPage(const int index) const
{
    if (index == 3)
    {
        // Delete the charts before creating again.
        while (QLayoutItem *layoutItem = ui.googleSheetSortByLineChartLayout->takeAt(0))
            delete layoutItem->widget();
    }

    if (index == 5)
    {
        // Delete the charts before creating again.
        while (QLayoutItem *layoutItem = ui.googleSheetSortByDateTimeChartLayout->takeAt(0))
            delete layoutItem->widget();
    }

    if (index == 7)
    {
        // Delete the charts before creating again.
        while (QLayoutItem *layoutItem = ui.twitterChartLayout->takeAt(0))
            delete layoutItem->widget();
    }
}

void NewMainGui::afterGotoPage(const int index) const
{
    if (index == 1)
    {
        // Ensure the top selection is checked if both are not checked.
        if (!ui.googleSheetMainMenuLineColourRadioButton->isChecked() && !ui.googleSheetMainMenuDateTimeRadioButton->isChecked())
            ui.googleSheetMainMenuLineColourRadioButton->setChecked(true);
    }

    if (index == 4)
    {
        // Remove the row upon loading the page.
        ui.googleSheetSortByDateTimeTable->setRowCount(0);
    }

    if (index == 6)
    {
        // Remove the row upon loading the page.
        ui.twitterMainMenuTable->setRowCount(0);
    }
}

/*
 * PAGE 3 - Google Sheet Sort By Line Charts.
 */

void NewMainGui::showGoogleSheetSortByLineBarChart()
{
    QVector<TrainServiceDisruptionData> data = trainServiceDisruptionSheetExtractor.getData();
    dataCounts dataCounts;
    QVector<int> counts = dataCounts.getGSCountLines(data);

    QBarSet *set0 = new QBarSet("North South Line");
    QBarSet *set1 = new QBarSet("East West Line");
    QBarSet *set2 = new QBarSet("North East Line");
    QBarSet *set3 = new QBarSet("Circle Line");
    QBarSet *set4 = new QBarSet("Downtown Line");
    QBarSet *set5 = new QBarSet("Other Line");

    set0->append(counts[0]);
    set0->setBrush(QColor(255, 38, 31));

    set1->append(counts[1]);
    set1->setBrush(QColor(0, 153, 54));

    set2->append(counts[2]);
    set2->setBrush(QColor(157, 32, 170));

    set3->append(counts[3]);
    set3->setBrush(QColor(251, 161, 25));

    set4->append(counts[4]);
    set4->setBrush(QColor(0, 85, 185));

    set5->append(counts[5]);
    set5->setBrush(QColor(111, 132, 117));

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    series->setLabelsVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("MRT Disruption Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QFont font = chart->titleFont();
    font.setBold(true);
    font.setPixelSize(25);

    chart->setTitleFont(font);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui.googleSheetSortByLineChartLayout->addWidget(chartView);
}

void NewMainGui::showGoogleSheetSortByLinePieChart()
{
    QVector<TrainServiceDisruptionData> data = trainServiceDisruptionSheetExtractor.getData();
    dataCounts dataCounts;
    QVector<int> counts = dataCounts.getGSCountLines(data);

    QPieSeries *series = new QPieSeries();
    series->append("North South Line", counts[0]);
    series->append("East West Line", counts[1]);
    series->append("North East Line", counts[2]);
    series->append("Circle Line", counts[3]);
    series->append("Downtown Line", counts[4]);
    series->append("Other Line", counts[5]);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    for (int i = 0; i < series->count(); i++)
    {
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        slice->setLabel(QString(slice->label() + " %1%").arg(100 * slice->percentage(), 0, 'f', 1));

        if (i == 0)
            slice->setBrush(QColor(255, 38, 31));
        else if (i == 1)
            slice->setBrush(QColor(0, 153, 54));
        else if (i == 2)
            slice->setBrush(QColor(157, 32, 170));
        else if (i == 3)
            slice->setBrush(QColor(251, 161, 25));
        else if (i == 4)
            slice->setBrush(QColor(0, 85, 185));
        else if (i == 5)
            slice->setBrush(QColor(111, 132, 117));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("MRT Disruption Pie Chart");

    QFont font = chart->titleFont();
    font.setBold(true);
    font.setPixelSize(25);

    chart->setTitleFont(font);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui.googleSheetSortByLineChartLayout->addWidget(chartView);
}

/*
 * PAGE 4 - Google Sheet Sort By DateTime.
 */

void NewMainGui::showGoogleSheetSortByDateTimeTable()
{
    QTableWidget *table = ui.googleSheetSortByDateTimeTable;
    table->setRowCount(0);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QVector<TrainServiceDisruptionData> trainServiceDisruptionsData = trainServiceDisruptionSheetExtractor.getData();

    for (TrainServiceDisruptionData &data : trainServiceDisruptionsData)
    {
        if (data.getStartDate().date().month() == ui.googleSheetSortByDateTimeMonthComboBox->currentIndex() + 1 &&
            data.getStartDate().date().year() == ui.googleSheetSortByDateTimeYearComboBox->currentText().toInt())
        {
            const qint32 rowIndex = table->rowCount();
            table->setRowCount(rowIndex + 1);
            table->setItem(rowIndex, 0, new QTableWidgetItem(data.getStartDate().date().toString("dd MMMM yyyy")));
            table->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(data.getDuration())));
            table->setItem(rowIndex, 2, new QTableWidgetItem(data.getLine()));
            table->setItem(rowIndex, 3, new QTableWidgetItem(data.getCategory()));
            table->setItem(rowIndex, 4, new QTableWidgetItem(data.getDescription()));
        }
    }
}

/*
 * PAGE 5 - Google Sheet Sort By DateTime Charts.
 */

void NewMainGui::showGoogleSheetSortByDateTimeBarChart()
{
    QVector<TrainServiceDisruptionData> data = trainServiceDisruptionSheetExtractor.getData();
    dataCounts dataCounts;
    QVector<int> counts = dataCounts.getYear(data, ui.googleSheetSortByDateTimeYearChartComboBox->currentText());

    QBarSet *set0 = new QBarSet("Under 30 minutes");
    QBarSet *set1 = new QBarSet("Under 1 hour");
    QBarSet *set2 = new QBarSet("Under 2 hours");
    QBarSet *set3 = new QBarSet("Over 2 hours");

    set0->append(counts[0]);
    set0->setBrush(QColor(255, 38, 31));

    set1->append(counts[1]);
    set1->setBrush(QColor(0, 153, 54));

    set2->append(counts[2]);
    set2->setBrush(QColor(157, 32, 170));

    set3->append(counts[3]);
    set3->setBrush(QColor(251, 161, 25));

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->setLabelsVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("MRT Disruption Duration Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QFont font = chart->titleFont();
    font.setBold(true);
    font.setPixelSize(25);

    chart->setTitleFont(font);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui.googleSheetSortByDateTimeChartLayout->addWidget(chartView);
}

/*
 * PAGE 6 - Twitter Main Menu.
 */

void NewMainGui::showTwitterSortByYearTable()
{
    QTableWidget *table = ui.twitterMainMenuTable;
    table->setRowCount(0);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QVector<TwitterTweetData> twitterTweetsData = tweetFilter.getTweets();

    for (TwitterTweetData &data : twitterTweetsData)
    {
        if (data.getTweetTimestamp().date().year() == ui.twitterMainMenuYearComboBox->currentText().toInt())
        {
            const qint32 rowIndex = table->rowCount();
            table->setRowCount(rowIndex + 1);
            table->setItem(rowIndex, 0, new QTableWidgetItem(data.getTweetTimestamp().date().toString("dd MMMM yyyy")));
            table->setItem(rowIndex, 1, new QTableWidgetItem(data.getTweetTrainLine()));
            table->setItem(rowIndex, 2, new QTableWidgetItem(data.getTweetMessage()));
        }
    }
}

/*
 * PAGE 7 - Twitter Charts.
 */

void NewMainGui::showTwitterSortByMonthLineChart()
{
    QVector<TwitterTweetData> data = tweetFilter.getTweets();
    dataCounts dataCounts;
    QVector<int> counts = dataCounts.getMonthCount(data);

    QLineSeries *series = new QLineSeries();
    series->setName("Mrt Line");
    series->append(QPoint(0, counts[0]));
    series->append(QPoint(1, counts[1]));
    series->append(QPoint(2, counts[2]));
    series->append(QPoint(3, counts[3]));
    series->append(QPoint(4, counts[4]));
    series->append(QPoint(5, counts[5]));
    series->append(QPoint(6, counts[6]));
    series->append(QPoint(7, counts[7]));
    series->append(QPoint(8, counts[8]));
    series->append(QPoint(9, counts[9]));
    series->append(QPoint(10, counts[10]));
    series->append(QPoint(11, counts[11]));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Train Disruption Incident Chart");

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    
    QValueAxis *axisY = new QValueAxis();

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisY);
    series->attachAxis(axisX);

    QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

    ui.twitterChartLayout->addWidget(chartView);
}

void NewMainGui::showTwitterSortByTrainLineBarChar()
{
    QVector<TwitterTweetData> data = tweetFilter.getTweets();
    dataCounts dataCounts;
    QVector<int> counts = dataCounts.getTDCountLines(data);

    QBarSet *set0 = new QBarSet("North South Line");
    QBarSet *set1 = new QBarSet("East West Line");
    QBarSet *set2 = new QBarSet("North East Line");
    QBarSet *set3 = new QBarSet("Circle Line");
    QBarSet *set4 = new QBarSet("Downtown Line");
    QBarSet *set5 = new QBarSet("Other Line");

    set0->append(counts[0]);
    set0->setBrush(QColor(255, 38, 31));

    set1->append(counts[1]);
    set1->setBrush(QColor(0, 153, 54));

    set2->append(counts[2]);
    set2->setBrush(QColor(157, 32, 170));

    set3->append(counts[3]);
    set3->setBrush(QColor(251, 161, 25));

    set4->append(counts[4]);
    set4->setBrush(QColor(0, 85, 185));

    set5->append(counts[5]);
    set5->setBrush(QColor(111, 132, 117));

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    series->setLabelsVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("MRT Breakdown Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QFont font = chart->titleFont();
    font.setBold(true);
    font.setPixelSize(25);

    chart->setTitleFont(font);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui.twitterChartLayout->addWidget(chartView);
}

/*
* GUI PAGE EVENTS
* 0 - Main Menu
* 1 - Google Sheet Main Menu.
* 2 - Google Sheet Sort By Line.
* 3 - Google Sheet Sort By Line Charts.
* 4 - Google Sheet Sort By DateTime.
* 5 - Google Sheet Sort By DateTime Charts.
* 6 - Twitter Main Menu.
* 7 - Twitter Charts.
*/

/*
 * PAGE 0 - Main Menu
 */

void NewMainGui::mainMenuButtonReleased()
{
    if (ui.mainMenuDataComboBox->currentIndex() == 0)
    {
        gotoPage(1);
        trainServiceDisruptionSheetExtractor.getData(true);
    }
    else if (ui.mainMenuDataComboBox->currentIndex() == 1)
    {
        gotoPage(6);
        twitterTweetsSearchExtractor.getData(true);
    }
}

/*
 * PAGE 1 - Google Sheet Main Menu.
 */

void NewMainGui::googleSheetMainMenuNextButtonReleased() const
{
    if (ui.googleSheetMainMenuLineColourRadioButton->isChecked())
        gotoPage(2);

    if (ui.googleSheetMainMenuDateTimeRadioButton->isChecked())
        gotoPage(4);
}

void NewMainGui::googleSheetMainMenuBackButtonReleased() const
{
    gotoPage(0);
}

/*
 * PAGE 2 - Google Sheet Sort By Line.
 */

void NewMainGui::googleSheetSortByLineBarChartButtonReleased()
{
    gotoPage(3);
    showGoogleSheetSortByLineBarChart();
}

void NewMainGui::googleSheetSortByLinePieChartButtonReleased()
{
    gotoPage(3);
    showGoogleSheetSortByLinePieChart();
}

void NewMainGui::googleSheetSortByLineBackButtonReleased() const
{
    gotoPage(1);
}

/*
 * PAGE 3 - Google Sheet Sort By Line Charts.
 */

void NewMainGui::googleSheetSortByLineChartBackButtonReleased() const
{
    gotoPage(2);
}

/*
 * PAGE 4 - Google Sheet Sort By DateTime.
 */

void NewMainGui::googleSheetSortByDateTimeBackButtonReleased() const
{
    gotoPage(1);
}

void NewMainGui::googleSheetSortByDateTimeChartButtonReleased()
{
    gotoPage(5);
    showGoogleSheetSortByDateTimeBarChart();
}

void NewMainGui::googleSheetSortByDateTimeGenerateButtonReleased()
{
    showGoogleSheetSortByDateTimeTable();
}

/*
 * PAGE 5 - Google Sheet Sort By DateTime Charts.
 */

void NewMainGui::googleSheetSortByDateTimeChartsBackButtonReleased() const
{
    gotoPage(4);
}

/*
 * PAGE 6 - Twitter Main Menu.
 */

void NewMainGui::twitterMainMenuBackButtonReleased() const
{
    gotoPage(0);
}

void NewMainGui::twitterMainMenuSortByTrainLineButtonReleased()
{
    gotoPage(7);
    showTwitterSortByTrainLineBarChar();
}

void NewMainGui::twitterMainMenuSortByMonthButtonReleased()
{
    gotoPage(7);
    showTwitterSortByMonthLineChart();
}

void NewMainGui::twitterMainMenuGenerateButtonReleased()
{
    showTwitterSortByYearTable();
}

/*
 * PAGE 7 - Twitter Charts.
 */

void NewMainGui::twitterChartsBackButtonReleased() const
{
    gotoPage(6);
}
