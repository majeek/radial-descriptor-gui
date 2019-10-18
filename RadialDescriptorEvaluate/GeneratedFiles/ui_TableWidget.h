/********************************************************************************
** Form generated from reading UI file 'TableWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEWIDGET_H
#define UI_TABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableWidget
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *TableWidget)
    {
        if (TableWidget->objectName().isEmpty())
            TableWidget->setObjectName(QStringLiteral("TableWidget"));
        TableWidget->resize(400, 300);
        gridLayout = new QGridLayout(TableWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(TableWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(TableWidget);

        QMetaObject::connectSlotsByName(TableWidget);
    } // setupUi

    void retranslateUi(QWidget *TableWidget)
    {
        TableWidget->setWindowTitle(QApplication::translate("TableWidget", "TableWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class TableWidget: public Ui_TableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEWIDGET_H
