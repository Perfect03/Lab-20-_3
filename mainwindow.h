#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include "themewidget.h"
#include <QSplitter>
#include <QPdfWriter>
#include <QFileDialog>

class MainWindow : public QWidget//
{
    Q_OBJECT
private slots:

    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void on_select_comboboxOnChangedSlot(const int index);
    void on_print_chart_slot();
    void on_select_dir_slot();
    void on_color_chart_slot();
    void on_reDraw();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QString filePath;
    QString homePath;
    QString homePathSavePdf;
    QFileSystemModel *fileModel;
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    QTableView *tableView;
    QPushButton *btnPrint;
    QPushButton *selectDir;
    QCheckBox *checkbox;
    QComboBox *combobox;
    QLabel *label, *label_path;
    ThemeWidget *themeWidget;
    QChartView *chartView;
    QChart *chartBar;
    QSplitter *splitter;
    ChartFileDataSqlite chartData;
    QList <QColor> colorColored;
    QList <QColor> colorBlack_White;
    bool flag_chart; // для определения типа графика
};

#endif // MAINWINDOW_H
