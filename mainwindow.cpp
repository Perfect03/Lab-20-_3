#include "mainwindow.h"
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>
#include <QtWidgets/QWidget>
// библиотеки для построения графиков
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
      //QMainWindow(parent)
{
    //Устанавливаем размер главного окна
    //this->resize(1500,500);
    //this->setGeometry(100, 100, 1500, 500);
    setWindowTitle("Laba3"); // заголовк окна
    resize(1500, 500); // стандартный размер
    //this->setStatusBar(new QStatusBar(this));
    //this->statusBar()->showMessage("Choosen Path: ");

    QString str = PRJ_PATH;
    homePath = str + "/InputData";

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(homePath);


    //Показать как дерево, пользуясь готовым видом:


    label_path = new QLabel("Choosen Path: "); // надпись с выбранным путём к файлу
    label_path->setText(homePath); // ставим в неё текст из переменной homePath

    label = new QLabel("Выберите тип диаграммы"); // надпись для выбора диаграммы

    combobox = new QComboBox();//выпадающий список с выбором графика
    //combobox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    btnPrint = new QPushButton("Печать графика"); //кнопка печати графика
    //btnPrint->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    checkbox = new QCheckBox("Черно-белый график"); //выпадающий список с выбором цвета графика
    //checkbox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    selectDir = new QPushButton("Выбор папки"); // кнопка выбора папки
    //selectDir->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    QHBoxLayout *layout = new QHBoxLayout(); // располагаем виджеты в горизонтальный     // компоновщик
    layout->addWidget(label);
    layout->addWidget(combobox);
    layout->addWidget(checkbox);
    layout->addWidget(btnPrint);
    layout->addWidget(selectDir);
    //layout->addStretch();
    layout->setAlignment(Qt::AlignCenter);
    //setLayout(layout);

    splitter = new QSplitter(parent);

    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // заполнять всё доступное пространство по вертикали

    treeView = new QTreeView();
    treeView->setModel(dirModel);
    treeView->expandAll();

    tableView = new QTableView(splitter); // табличное представление для файловой модели
    tableView->setModel(fileModel);

    treeView->setHeaderHidden(true); // скрываем заголовок дерева
    treeView->hideColumn(1); // также выключаем ненужные столбцы

    //1.Добавление диаграммы

    //themeWidget = new ThemeWidget(); // виджет для диаграммы
    //chartView = new QChartView(splitter);

    //chartBar =  themeWidget->createPieChart();
    //chartView = new QChartView(chartBar); // создаём графики

    //splitter->addWidget(chartView);
    //setCentralWidget(splitter);
    splitter->setStretchFactor(0, 1); // устанавливаем начальное положение разделителя
    splitter->setStretchFactor(1, 4);

    //splitter->addWidget(treeView);
    //splitter->addWidget(chartView);
    //splitter->addWidget(tableView);
    //setCentralWidget(splitter);


    QVBoxLayout *layout_vertical = new QVBoxLayout(this); // вертикальный компоновщик
    layout_vertical->addLayout(layout);
    layout_vertical->addWidget(splitter);
    layout_vertical->addWidget(label_path);
    //layout_vertical->addStretch();
    //setLayout(layout_vertical);

    QItemSelectionModel *selectionModel = tableView->selectionModel();
    QModelIndex rootIx = fileModel->index(0, 0, QModelIndex());//корневой элемент

    QModelIndex indexHomePath = fileModel->index(homePath);
    QFileInfo fileInfo = fileModel->fileInfo(indexHomePath);

    combobox->addItem("Bar Chart"); // добавляем в список виды диаграмм
    combobox->addItem("Pie Chart");

    /* Рассмотрим способы обхода содержимого папок на диске.
     * Предлагается вариант решения, которы может быть применен для более сложных задач.
     * Итак, если требуется выполнить анализ содержимого папки, то необходимо организовать обход содержимого. Обход выполняем относительно модельного индекса.
     * Например:*/
    if (fileInfo.isDir()) {
        /*
         * Если fileInfo папка то заходим в нее, чтобы просмотреть находящиеся в ней файлы.
         * Если нужно просмотреть все файлы, включая все вложенные папки, то нужно организовать рекурсивный обход.
        */
        QDir dir  = fileInfo.dir();

        if (dir.cd(fileInfo.fileName())) {
            /**
             * Если зашли в папку, то пройдемся по контейнеру QFileInfoList ,полученного методом entryInfoList,
             * */

            foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Type)) {
                qDebug() << inf.fileName() << "---" << inf.size();
            }

            dir.cdUp();// выходим из папки
        }
    }

    QDir dir = fileInfo.dir();

    foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Type)) {

        qDebug() << inf.fileName() << "---" << inf.size();
    }


    //Выполнение соединения слота и сигнала при выборе элемента в TreeView
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
    connect(combobox, &QComboBox::currentIndexChanged, this, &MainWindow::on_select_comboboxOnChangedSlot);// выбор графика
    connect (btnPrint, SIGNAL(clicked()), this, SLOT(on_print_chart_slot())); //печать графика
    connect (selectDir, SIGNAL(clicked()), this, SLOT(on_select_dir_slot())); //выбор папки
    connect (checkbox, SIGNAL(toggled(bool)), this, SLOT(on_color_chart_slot())); // смена цвета

    //Пример организации установки курсора в TableView относительно модельного индекса
    QItemSelection toggleSelection;
    QModelIndex topLeft;
    topLeft = fileModel->index(homePath);
    fileModel->setRootPath(homePath);

    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);

    tableView->setRootIndex(fileModel->setRootPath(homePath));
}

// метод смены цвета диаграммы
void MainWindow::on_color_chart_slot(){

}

// выбор папки и смена пути
void MainWindow::on_select_dir_slot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
        homePath = dialog.selectedFiles().first();;

   tableView->setRootIndex(fileModel->setRootPath(homePath));
}

//Печать графика через QPdfWriter
void MainWindow::on_print_chart_slot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
        homePathSavePdf = dialog.selectedFiles().first();

   // tableView->setRootIndex(fileModel->setRootPath(homePath));
    QPdfWriter writer(homePathSavePdf + "/" + "grafic.pdf");

    writer.setCreator("Author");// Создатель документа
    writer.setPageSize(QPageSize::A4);// Устанавливаем размер страницы А4

    QPainter painter(&writer);

    chart_view->render(&painter);
    painter.end();
}

//Слот для обработки выбора элемента в TableView, выбор осуществляется с помощью курсора

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    //Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = tableView->selectionModel()->currentIndex();
    QModelIndexList indexs =  selected.indexes();
    filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = fileModel->filePath(ix);
        label_path->setText(filePath);
        //this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));
    }

    //TODO: !!!!!
    /*
    Тут простейшая обработка ширины первого столбца относительно длины названия папки.
    Это для удобства, что бы при выборе папки имя полностью отображалась в  первом столбце.
    Требуется доработка(переработка).
    */
    int length = 200;
    int dx = 30;

    if (fileModel->fileName(index).length() * dx > length) {
        length = length + fileModel->fileName(index).length() * dx;
        qDebug() << "r = " << index.row() << "c = " << index.column() << fileModel->fileName(index) << fileModel->fileInfo(
                     index).size();

    }

    //tableView->header()->resizeSection(index.column(), length + dirModel->fileName(index).length());
    themeWidget->CreateData(chartData, filePath);
    chartBar =  themeWidget->createBarChart(5);//createPieChart();
    chartView = new QChartView(chartBar);
    splitter->addWidget(chartView);
    chartView->setChart(chartBar);
}

void MainWindow::on_select_comboboxOnChangedSlot(const int index)
{
    //splitter->deleteLater();
    try
    {
        switch (index) // получаем из выбранного индекса тип отображения
        {
        case 0:
            //chartBar =  themeWidget->createBarChart(10);
            //chartView = new QChartView(chartBar);
            //splitter->addWidget(chartView);
            chartBar =  themeWidget->createBarChart(5); 
            //createPieChart()
            // устанавливаем круговую диаграмму
            break;
        case 1:
            //chartBar =  themeWidget->createPieChart();
            //chartView = new QChartView(chartBar);
            //splitter->addWidget(chartView);
            chartBar =  themeWidget->createPieChart();
            // устанавливаем вертикальную диаграмму
            break;
        default:
            throw std::runtime_error("Unknown display type selected."); // такой ситуации быть не должно, по этому сообщаем о ней
            break;
        }
    chartView->setChart(chartBar);
    }
    catch (const std::runtime_error &e)
    {
        QMessageBox::about(this, "Error", e.what()); // сообщаем что в процессе выбора вида отображения что-то пошло не так
    }
}

MainWindow::~MainWindow()
{

}