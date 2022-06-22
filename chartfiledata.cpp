#include "chartfiledata.h"
#include <QMessageBox>

DataTable ChartFileDataSqlite::getData (QString path) // получение данных из sql
{
    DataTable data; // данные
    DataList dataList; // таблица данных, на основании которой будем строить график
    qreal yValue(0);
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(path); // записываем данные из файла

    if (!dbase.open()) { // исключение
        QMessageBox msg; // окно с текстом об ошибке
        msg.setText("База данных не открыта." + path);
        msg.exec(); // функцией exec отображаем его
    }

    else
    {
        QSqlQuery query("SELECT * FROM " + dbase.tables().takeFirst());
            while (query.next()) { // цикл по элементам БД
                QString name = query.value(0).toString(); // название элемента
                QPointF salary(query.value(1).toDouble(),rand()); // рандомное значение, оно не пригодится
                dataList << Data(salary, name); // запись данных оператором <<
                qDebug() << "name is " << name << ". salary is " << salary; // текст вывода
            }
    }

   data << dataList;
   return data;
}

DataTable ChartFileDataJson::getData(QString path) // получение данных из json
{
    DataTable data; // данные
    DataList dataList; // таблица данных, на основании которой будем строить график
    QString key;
    QFile file;
    file.setFileName(path); // читаем файл
    file.open(QIODevice::ReadOnly | QIODevice::Text);// открываем файл на чтение
    key = file.readAll(); // сначала читаем все элементы
    file.close(); // и сразу закрываем файл
    QJsonDocument doc = QJsonDocument::fromJson(key.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["11"].toArray(); // формируем массив объектов
    foreach (const QJsonValue & value, jsonArray) // и проходим по нему
    {
        if (value.isObject()) // если объект существует, считываем данные
        {
            QJsonObject obj = value.toObject();
            QString name = obj["key"].toString();
            QPointF salary(obj["ID"].toInt(),rand());
            dataList << Data(salary, name); // запись в таблицу данных
        }
    }
    //std::sort (data.begin(), data.end());
    data << dataList;
    return data;
}