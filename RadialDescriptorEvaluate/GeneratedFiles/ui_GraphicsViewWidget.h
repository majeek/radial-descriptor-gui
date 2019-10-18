/********************************************************************************
** Form generated from reading UI file 'GraphicsViewWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSVIEWWIDGET_H
#define UI_GRAPHICSVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicsViewWidget
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *GraphicsViewWidget)
    {
        if (GraphicsViewWidget->objectName().isEmpty())
            GraphicsViewWidget->setObjectName(QStringLiteral("GraphicsViewWidget"));
        GraphicsViewWidget->resize(400, 300);
        gridLayout = new QGridLayout(GraphicsViewWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(GraphicsViewWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        retranslateUi(GraphicsViewWidget);

        QMetaObject::connectSlotsByName(GraphicsViewWidget);
    } // setupUi

    void retranslateUi(QWidget *GraphicsViewWidget)
    {
        GraphicsViewWidget->setWindowTitle(QApplication::translate("GraphicsViewWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphicsViewWidget: public Ui_GraphicsViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSVIEWWIDGET_H
