#ifndef JOURNALS_H
#define JOURNALS_H

#include <QString>
#include <QTextStream>

class Journals
{
    QString name;
    QString date;
    int pages;
public:
    Journals();
    Journals(QString name,QString date, int pages);
    Journals(const Journals& other);
    ~Journals();
    QString getname();
    QString getdate();
    int getpages();
    bool operator > (const Journals& other);
    bool operator < (const Journals& other);
    friend QTextStream& operator >> (QTextStream& in, Journals& j);
    Journals& operator = (const Journals& other);
    QString toString();
    bool isEmpty();
};

#endif // JOURNALS_H
