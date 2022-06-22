#include "chartfiledata.h"
#include <QMessageBox>

DataTable ChartFileDataSqlite::getData (QString path) // ��������� ������ �� sql
{
    DataTable data; // ������
    DataList dataList; // ������� ������, �� ��������� ������� ����� ������� ������
    qreal yValue(0);
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(path); // ���������� ������ �� �����

    if (!dbase.open()) { // ����������
        QMessageBox msg; // ���� � ������� �� ������
        msg.setText("���� ������ �� �������." + path);
        msg.exec(); // �������� exec ���������� ���
    }

    else
    {
        QSqlQuery query("SELECT * FROM " + dbase.tables().takeFirst());
            while (query.next()) { // ���� �� ��������� ��
                QString name = query.value(0).toString(); // �������� ��������
                QPointF salary(query.value(1).toDouble(),rand()); // ��������� ��������, ��� �� ����������
                dataList << Data(salary, name); // ������ ������ ���������� <<
                qDebug() << "name is " << name << ". salary is " << salary; // ����� ������
            }
    }

   data << dataList;
   return data;
}

DataTable ChartFileDataJson::getData(QString path) // ��������� ������ �� json
{
    DataTable data; // ������
    DataList dataList; // ������� ������, �� ��������� ������� ����� ������� ������
    QString key;
    QFile file;
    file.setFileName(path); // ������ ����
    file.open(QIODevice::ReadOnly | QIODevice::Text);// ��������� ���� �� ������
    key = file.readAll(); // ������� ������ ��� ��������
    file.close(); // � ����� ��������� ����
    QJsonDocument doc = QJsonDocument::fromJson(key.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["11"].toArray(); // ��������� ������ ��������
    foreach (const QJsonValue & value, jsonArray) // � �������� �� ����
    {
        if (value.isObject()) // ���� ������ ����������, ��������� ������
        {
            QJsonObject obj = value.toObject();
            QString name = obj["key"].toString();
            QPointF salary(obj["ID"].toInt(),rand());
            dataList << Data(salary, name); // ������ � ������� ������
        }
    }
    //std::sort (data.begin(), data.end());
    data << dataList;
    return data;
}