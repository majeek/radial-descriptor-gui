/********************************************************************************
** Form generated from reading UI file 'DebugWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGWIDGET_H
#define UI_DEBUGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebugWidget
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEditDebug;

    void setupUi(QWidget *DebugWidget)
    {
        if (DebugWidget->objectName().isEmpty())
            DebugWidget->setObjectName(QStringLiteral("DebugWidget"));
        DebugWidget->resize(959, 620);
        gridLayout = new QGridLayout(DebugWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEditDebug = new QTextEdit(DebugWidget);
        textEditDebug->setObjectName(QStringLiteral("textEditDebug"));

        gridLayout->addWidget(textEditDebug, 0, 0, 1, 1);


        retranslateUi(DebugWidget);

        QMetaObject::connectSlotsByName(DebugWidget);
    } // setupUi

    void retranslateUi(QWidget *DebugWidget)
    {
        DebugWidget->setWindowTitle(QApplication::translate("DebugWidget", "DebugWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class DebugWidget: public Ui_DebugWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGWIDGET_H
