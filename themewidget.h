#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QList>
#include <QDataStream>
#include <QPair>
#include <QString>
#include <QPointF>
#include "chartfiledata.h"

class QComboBox;
class QCheckBox;


class QChartView;
class QChart;

class ThemeWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = nullptr);
    ~ThemeWidget();

private Q_SLOTS:
    void updateUI();

private:
    QList <QColor> color;
    int count_Chart;
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    QComboBox *createThemeBox() const;
    QComboBox *createAnimationBox() const;
    QComboBox *createLegendBox() const;
    void connectSignals();
public:
    QChart *createPieChart(DataTable mdataTable);
    void CreateData(ChartFileData &data, QString path);
    void Recolor(QList <QColor> color);
    void countChart(int countChart);
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
    QChart *createScatterChart() const;

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;

    QList<QChartView *> m_charts;
    DataTable m_dataTable;
    QComboBox *m_themeComboBox;
    QCheckBox *m_antialiasCheckBox;
    QComboBox *m_animatedComboBox;
    QComboBox *m_legendComboBox;
};

#endif /* THEMEWIDGET_H */
