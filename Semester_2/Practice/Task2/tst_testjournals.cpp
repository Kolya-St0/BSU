#include <QCoreApplication>
#include <QtTest>
#include "journals.h"

class TestJournals : public QObject
{
    Q_OBJECT

public:
    TestJournals();
    ~TestJournals();

private slots:

    void test_getname();
    void test_getdate();
    void test_getpages();

    void test_operatorGreaterThan();
    void test_operatorLessThan();
    void test_operatorAssignment();
    void test_operatorStreamInput();

    void test_toString();
    void test_isEmpty();
};

TestJournals::TestJournals() = default;
TestJournals::~TestJournals() = default;

void TestJournals::test_getname()
{
    Journals journal("PhysicsToday", "20.08.2023", 25);
    QCOMPARE(journal.getname(), QString("PhysicrrsToday"));
}

void TestJournals::test_getdate()
{
    Journals journal("ChemistryReview", "07.10.2002", 40);
    QCOMPARE(journal.getdate(), QString("07.10.2002"));
}

void TestJournals::test_getpages()
{
    Journals journal("MathInsights", "05.06.2017", 60);
    QCOMPARE(journal.getpages(), 60);
}

void TestJournals::test_operatorGreaterThan()
{
    Journals journal1("Biology", "01.02.2022", 20);
    Journals journal2("Astronomy", "01.02.2022", 20);

    QVERIFY(journal1 > journal2);
    QVERIFY(!(journal2 > journal1));
}

void TestJournals::test_operatorLessThan()
{
    Journals journal1("Geology", "2023-01-01", 15);
    Journals journal2("Physics", "2023-01-01", 15);

    QVERIFY(journal1 < journal2);
    QVERIFY(!(journal2 < journal1));
}

void TestJournals::test_operatorAssignment()
{
    Journals journal1("ComputerScience", "01.05.2014", 45);
    Journals journal2;
    journal2 = journal1;

    QCOMPARE(journal2.getname(), journal1.getname());
    QCOMPARE(journal2.getdate(), journal1.getdate());
    QCOMPARE(journal2.getpages(), journal1.getpages());
}

void TestJournals::test_operatorStreamInput()
{
    QString data = "Quantum_Journal 01.04.2023 35";
    QTextStream in(&data);

    Journals journal;
    in >> journal;

    QCOMPARE(journal.getname(), QString("Quantum_Journal"));
    QCOMPARE(journal.getdate(), QString("01.04.2023"));
    QCOMPARE(journal.getpages(), 35);
}

void TestJournals::test_toString()
{
    Journals journal("MedicineToday", "13.09.2020", 50);
    QString expected = "MedicineToday 13.09.2020 50";
    QCOMPARE(journal.toString(), expected);
}

void TestJournals::test_isEmpty()
{
    Journals emptyJournal;
    Journals nonEmptyJournal("Science", "08.09.2000", 30);

    QVERIFY(emptyJournal.isEmpty());
    QVERIFY(!nonEmptyJournal.isEmpty());
}
QTEST_MAIN(TestJournals)

#include "tst_testjournals.moc"
