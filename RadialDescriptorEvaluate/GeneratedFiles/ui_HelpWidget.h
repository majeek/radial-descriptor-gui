/********************************************************************************
** Form generated from reading UI file 'HelpWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWIDGET_H
#define UI_HELPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpWidget
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_14;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *HelpWidget)
    {
        if (HelpWidget->objectName().isEmpty())
            HelpWidget->setObjectName(QStringLiteral("HelpWidget"));
        HelpWidget->resize(783, 576);
        gridLayout_2 = new QGridLayout(HelpWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_2 = new QGroupBox(HelpWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QFont font;
        font.setPointSize(12);
        groupBox_2->setFont(font);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 6, 0, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font);

        gridLayout->addWidget(label_12, 7, 0, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 8, 0, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 9, 0, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font);

        gridLayout->addWidget(label_15, 10, 0, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 11, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(HelpWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);


        retranslateUi(HelpWidget);

        QMetaObject::connectSlotsByName(HelpWidget);
    } // setupUi

    void retranslateUi(QWidget *HelpWidget)
    {
        HelpWidget->setWindowTitle(QApplication::translate("HelpWidget", "Help", 0));
        groupBox_2->setTitle(QApplication::translate("HelpWidget", "Help", 0));
        label_4->setText(QApplication::translate("HelpWidget", "Sample Ratio - Defines the size of the vector as a ratio", 0));
        label_8->setText(QApplication::translate("HelpWidget", "                       between 1 and max radius.", 0));
        label_5->setText(QApplication::translate("HelpWidget", "Dominant Set Size - Defines the number of the vectors", 0));
        label_7->setText(QApplication::translate("HelpWidget", "                               to be chosen for the dominant matrix.", 0));
        label_6->setText(QApplication::translate("HelpWidget", "Reset - Clears all settings. Resets the program.", 0));
        label_9->setText(QApplication::translate("HelpWidget", "Draw Descriptor Matrix - Draws an image of descriptor signatures", 0));
        label_10->setText(QApplication::translate("HelpWidget", "                                     where each signature is drawn as a row of the image.", 0));
        label_12->setText(QApplication::translate("HelpWidget", "Plot Dominant Set - Plots the dominant set as functions, before transformation.", 0));
        label_11->setText(QApplication::translate("HelpWidget", "Dominant Set FT - Plots the dominant set after its transformation", 0));
        label_13->setText(QApplication::translate("HelpWidget", "                                using Fourier transform.", 0));
        label_15->setText(QApplication::translate("HelpWidget", "Plot Descriptor Matrix - Plots the descriptor signatures", 0));
        label_14->setText(QApplication::translate("HelpWidget", "                                   where each signature is a function plot in the graph.", 0));
        groupBox->setTitle(QApplication::translate("HelpWidget", "About", 0));
        label->setText(QApplication::translate("HelpWidget", "Radial Descriptor v0.4a", 0));
        label_2->setText(QApplication::translate("HelpWidget", "Majeed Kassis", 0));
        label_3->setText(QApplication::translate("HelpWidget", "majeek@cs.bgu.ac.il", 0));
    } // retranslateUi

};

namespace Ui {
    class HelpWidget: public Ui_HelpWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWIDGET_H
