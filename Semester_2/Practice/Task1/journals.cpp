#include "journals.h"

Journals::Journals()
{
    pages = 0;
}

Journals::Journals(QString name,QString date,int pages)
{
    this->name = name;
    this->date = date;
    this->pages = pages;
}

Journals::Journals(const Journals &other)
{
    name = other.name;
    date = other.date;
    pages = other.pages;
}

Journals::~Journals(){}

QString Journals::getname()
{
    return name;
}

QString Journals::getdate()
{
    return date;
}

int Journals::getpages()
{
    return pages;
}

bool Journals::operator > (const Journals& other)
{
    return name > other.name;
}

bool Journals::operator < (const Journals& other)
{
    return name < other.name;
}

QTextStream& operator >> (QTextStream& in, Journals& j)
{
    in >> j.name >> j.date >> j.pages;
    return in;
}

Journals& Journals::operator = (const Journals& other)
{
    name = other.name;
    date = other.date;
    pages = other.pages;
    return *this;
}

QString Journals::toString()
{
    return(name + " " + date + " " + QString::number(pages));
}

bool Journals::isEmpty()
{
    return(name.isEmpty() && date.isEmpty() && pages == 0);
}
