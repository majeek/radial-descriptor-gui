/********************************************************************************
** Form generated from reading UI file 'PleaseWaitWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLEASEWAITWIDGET_H
#define UI_PLEASEWAITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PleaseWaitWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *labelStatus;

    void setupUi(QWidget *PleaseWaitWidget)
    {
        if (PleaseWaitWidget->objectName().isEmpty())
            PleaseWaitWidget->setObjectName(QStringLiteral("PleaseWaitWidget"));
        PleaseWaitWidget->resize(645, 108);
        gridLayout = new QGridLayout(PleaseWaitWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelStatus = new QLabel(PleaseWaitWidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        QFont font;
        font.setPointSize(24);
        labelStatus->setFont(font);
        labelStatus->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelStatus, 0, 0, 1, 1);


        retranslateUi(PleaseWaitWidget);

        QMetaObject::connectSlotsByName(PleaseWaitWidget);
    } // setupUi

    void retranslateUi(QWidget *PleaseWaitWidget)
    {
        PleaseWaitWidget->setWindowTitle(QApplication::translate("PleaseWaitWidget", "Please Wait...", 0));
        labelStatus->setText(QApplication::translate("PleaseWaitWidget", "null", 0));
    } // retranslateUi

};

namespace Ui {
    class PleaseWaitWidget: public Ui_PleaseWaitWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLEASEWAITWIDGET_H
