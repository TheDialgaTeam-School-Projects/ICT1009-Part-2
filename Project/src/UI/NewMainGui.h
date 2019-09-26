#pragma once

#include "ui_NewMainGui.h"

#include "src/WebCrawler/Extractor/TrainServiceDisruptionSheetExtractor.h"
#include "src/WebCrawler/Extractor/TwitterTweetsSearchExtractor.h"
#include "src/TweetFilter.h"

class NewMainGui final: public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMainGui(QWidget *parent = Q_NULLPTR);

private:
    /**
     * \brief The UI class generated from QT.
     */
    Ui::MainGuiClass ui;

    /**
     * \brief Class that extract information about train service disruption in google sheets.
     */
    TrainServiceDisruptionSheetExtractor trainServiceDisruptionSheetExtractor;

    /**
     * \brief Class that extract information about train service disruption in twitter.
     */
    TwitterTweetsSearchExtractor twitterTweetsSearchExtractor;

    TweetFilter tweetFilter;

    /**
     * \brief Goto the selected page index.
     * \param index Page index to go into.
     */
    void gotoPage(int index) const;

    /**
     * \brief Events triggered before going into the selected page.
     * \param index Page index events.
     */
    void beforeGotoPage(int index) const;

    /**
     * \brief Events triggered after going into the selected page.
     * \param index Page index events.
     */
    void afterGotoPage(int index) const;

    /*
     * PAGE 3 - Google Sheet Sort By Line Charts.
     */

    /**
     * \brief Show Google Sheet Sort By Line Bar Chart.
     */
    void showGoogleSheetSortByLineBarChart();

    /**
     * \brief Show Google Sheet Sort By Line Pie Chart.
     */
    void showGoogleSheetSortByLinePieChart();

    /*
     * PAGE 4 - Google Sheet Sort By DateTime.
     */

    /**
     * \brief Show Google Sheet Sort By DateTime Table.
     */
    void showGoogleSheetSortByDateTimeTable();

    /*
     * PAGE 5 - Google Sheet Sort By DateTime Charts.
     */

    /**
     * \brief Show Google Sheet Sort By DateTime Bar Chart.
     */
    void showGoogleSheetSortByDateTimeBarChart();

    /*
     * PAGE 6 - Twitter Main Menu.
     */

    /**
     * \brief Show Twitter Sort By Year Table.
     */
    void showTwitterSortByYearTable();

    /*
     * PAGE 7 - Twitter Charts.
     */

    /**
     * \brief Show Twitter Sort By Month Line Chart.
     */
    void showTwitterSortByMonthLineChart();

    /**
     * \brief Show Twitter Sort By Train Line Bar Chart.
     */
    void showTwitterSortByTrainLineBarChar();

private slots:
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

    void mainMenuButtonReleased();

    /*
     * PAGE 1 - Google Sheet Main Menu.
     */

    void googleSheetMainMenuNextButtonReleased() const;
    void googleSheetMainMenuBackButtonReleased() const;

    /*
     * PAGE 2 - Google Sheet Sort By Line.
     */

    void googleSheetSortByLineBarChartButtonReleased();
    void googleSheetSortByLinePieChartButtonReleased();
    void googleSheetSortByLineBackButtonReleased() const;

    /*
     * PAGE 3 - Google Sheet Sort By Line Charts.
     */

    void googleSheetSortByLineChartBackButtonReleased() const;

    /*
     * PAGE 4 - Google Sheet Sort By DateTime.
     */

    void googleSheetSortByDateTimeBackButtonReleased() const;
    void googleSheetSortByDateTimeChartButtonReleased();
    void googleSheetSortByDateTimeGenerateButtonReleased();

    /*
     * PAGE 5 - Google Sheet Sort By DateTime Charts.
     */

    void googleSheetSortByDateTimeChartsBackButtonReleased() const;

    /*
     * PAGE 6 - Twitter Main Menu.
     */

    void twitterMainMenuBackButtonReleased() const;
    void twitterMainMenuSortByTrainLineButtonReleased();
    void twitterMainMenuSortByMonthButtonReleased();
    void twitterMainMenuGenerateButtonReleased();

    /*
     * PAGE 7 - Twitter Charts.
     */

    void twitterChartsBackButtonReleased() const;
};
