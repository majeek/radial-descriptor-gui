/********************************************************************************
** Form generated from reading UI file 'TotalProgress.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOTALPROGRESS_H
#define UI_TOTALPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_TotalProgress
{
public:
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBarTotalProgress;
    QLabel *labelCompleteImages;
    QLabel *label;
    QLabel *labelTotalImages;

    void setupUi(QDialog *TotalProgress)
    {
        if (TotalProgress->objectName().isEmpty())
            TotalProgress->setObjectName(QStringLiteral("TotalProgress"));
        TotalProgress->resize(1101, 46);
        horizontalLayout = new QHBoxLayout(TotalProgress);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressBarTotalProgress = new QProgressBar(TotalProgress);
        progressBarTotalProgress->setObjectName(QStringLiteral("progressBarTotalProgress"));
        progressBarTotalProgress->setValue(0);
        progressBarTotalProgress->setTextVisible(false);

        horizontalLayout->addWidget(progressBarTotalProgress);

        labelCompleteImages = new QLabel(TotalProgress);
        labelCompleteImages->setObjectName(QStringLiteral("labelCompleteImages"));

        horizontalLayout->addWidget(labelCompleteImages);

        label = new QLabel(TotalProgress);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        labelTotalImages = new QLabel(TotalProgress);
        labelTotalImages->setObjectName(QStringLiteral("labelTotalImages"));

        horizontalLayout->addWidget(labelTotalImages);


        retranslateUi(TotalProgress);

        QMetaObject::connectSlotsByName(TotalProgress);
    } // setupUi

    void retranslateUi(QDialog *TotalProgress)
    {
        TotalProgress->setWindowTitle(QApplication::translate("TotalProgress", "Total Progress", 0));
        labelCompleteImages->setText(QApplication::translate("TotalProgress", "0", 0));
        label->setText(QApplication::translate("TotalProgress", "/", 0));
        labelTotalImages->setText(QApplication::translate("TotalProgress", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class TotalProgress: public Ui_TotalProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOTALPROGRESS_H
