/********************************************************************************
** Form generated from reading UI file 'RadialDescriptorQt5.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIALDESCRIPTORQT5_H
#define UI_RADIALDESCRIPTORQT5_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RadialDescriptorGUIClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_12;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_24;
    QCheckBox *checkBoxBackgroundColorTab3;
    QSpinBox *spinBoxBackgroundColorTab3;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_17;
    QLineEdit *lineEditAllPointsSamplingSamplingRadius;
    QLabel *label_18;
    QLineEdit *lineEditAllPointsNumberOfLevels;
    QLabel *label_19;
    QComboBox *comboBoxPointInAllPointsInterpolationWeight;
    QHBoxLayout *horizontalLayout_25;
    QCheckBox *checkBoxMinDistanceTab3;
    QLineEdit *lineEditMinimumDistanceBetweenTwoPointsTab3;
    QLabel *label_32;
    QLineEdit *lineEditImageBlurTab3;
    QLabel *label_35;
    QLineEdit *lineEditKernelSizeTab3;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_40;
    QLineEdit *lineEditMinimumVarianceTab3;
    QLabel *label_26;
    QLineEdit *lineEditSamplingRadiusTab3;
    QLabel *label_27;
    QLineEdit *lineEditNumberOfLevelsTab3;
    QLabel *label_31;
    QComboBox *comboBoxLevel0WeightTab3;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_33;
    QLineEdit *lineEditDistanceHistogramNumberOfLevelsTab3;
    QLabel *label_39;
    QLineEdit *lineEditDistanceHistogramLevelStepTab3;
    QLabel *label_36;
    QLineEdit *lineEditNumberOfClusters;
    QCheckBox *checkBoxNumberOfPointsTab3;
    QLineEdit *lineEditNumberOfPointsTab3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_45;
    QLabel *labelInitiateAllProgress;
    QHBoxLayout *horizontalLayout_41;
    QLabel *label_46;
    QLineEdit *lineEditPersistencePath;
    QPushButton *pushButtonPersistencePath;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_44;
    QLineEdit *lineEditResultsStoragePathTab5;
    QPushButton *pushButtonChooseResultsStoragePathTab5;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_42;
    QLineEdit *lineEditTrainPath;
    QPushButton *pushButtonTrainPath;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_43;
    QLineEdit *lineEditTestPath;
    QPushButton *pushButtonTestPath;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_37;
    QComboBox *comboBoxHistogramComparisonMethodTab4;
    QCheckBox *checkBoxLoadFromPersistence;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonSummarizeResults;
    QPushButton *pushButtonInitiateProcess;

    void setupUi(QMainWindow *RadialDescriptorGUIClass)
    {
        if (RadialDescriptorGUIClass->objectName().isEmpty())
            RadialDescriptorGUIClass->setObjectName(QStringLiteral("RadialDescriptorGUIClass"));
        RadialDescriptorGUIClass->resize(947, 455);
        QFont font;
        font.setKerning(true);
        RadialDescriptorGUIClass->setFont(font);
        RadialDescriptorGUIClass->setToolButtonStyle(Qt::ToolButtonTextOnly);
        centralWidget = new QWidget(RadialDescriptorGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_12 = new QVBoxLayout(centralWidget);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMovable(false);
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout = new QGridLayout(tab_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        checkBoxBackgroundColorTab3 = new QCheckBox(tab_3);
        checkBoxBackgroundColorTab3->setObjectName(QStringLiteral("checkBoxBackgroundColorTab3"));
        checkBoxBackgroundColorTab3->setChecked(false);

        horizontalLayout_24->addWidget(checkBoxBackgroundColorTab3);

        spinBoxBackgroundColorTab3 = new QSpinBox(tab_3);
        spinBoxBackgroundColorTab3->setObjectName(QStringLiteral("spinBoxBackgroundColorTab3"));
        spinBoxBackgroundColorTab3->setMaximum(255);
        spinBoxBackgroundColorTab3->setValue(175);

        horizontalLayout_24->addWidget(spinBoxBackgroundColorTab3);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_17 = new QLabel(tab_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_20->addWidget(label_17);

        lineEditAllPointsSamplingSamplingRadius = new QLineEdit(tab_3);
        lineEditAllPointsSamplingSamplingRadius->setObjectName(QStringLiteral("lineEditAllPointsSamplingSamplingRadius"));

        horizontalLayout_20->addWidget(lineEditAllPointsSamplingSamplingRadius);

        label_18 = new QLabel(tab_3);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_20->addWidget(label_18);

        lineEditAllPointsNumberOfLevels = new QLineEdit(tab_3);
        lineEditAllPointsNumberOfLevels->setObjectName(QStringLiteral("lineEditAllPointsNumberOfLevels"));

        horizontalLayout_20->addWidget(lineEditAllPointsNumberOfLevels);

        label_19 = new QLabel(tab_3);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_20->addWidget(label_19);

        comboBoxPointInAllPointsInterpolationWeight = new QComboBox(tab_3);
        comboBoxPointInAllPointsInterpolationWeight->setObjectName(QStringLiteral("comboBoxPointInAllPointsInterpolationWeight"));

        horizontalLayout_20->addWidget(comboBoxPointInAllPointsInterpolationWeight);


        horizontalLayout_24->addLayout(horizontalLayout_20);


        gridLayout_8->addLayout(horizontalLayout_24, 0, 0, 1, 1);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        checkBoxMinDistanceTab3 = new QCheckBox(tab_3);
        checkBoxMinDistanceTab3->setObjectName(QStringLiteral("checkBoxMinDistanceTab3"));
        checkBoxMinDistanceTab3->setChecked(true);

        horizontalLayout_25->addWidget(checkBoxMinDistanceTab3);

        lineEditMinimumDistanceBetweenTwoPointsTab3 = new QLineEdit(tab_3);
        lineEditMinimumDistanceBetweenTwoPointsTab3->setObjectName(QStringLiteral("lineEditMinimumDistanceBetweenTwoPointsTab3"));

        horizontalLayout_25->addWidget(lineEditMinimumDistanceBetweenTwoPointsTab3);

        label_32 = new QLabel(tab_3);
        label_32->setObjectName(QStringLiteral("label_32"));

        horizontalLayout_25->addWidget(label_32);

        lineEditImageBlurTab3 = new QLineEdit(tab_3);
        lineEditImageBlurTab3->setObjectName(QStringLiteral("lineEditImageBlurTab3"));

        horizontalLayout_25->addWidget(lineEditImageBlurTab3);

        label_35 = new QLabel(tab_3);
        label_35->setObjectName(QStringLiteral("label_35"));

        horizontalLayout_25->addWidget(label_35);

        lineEditKernelSizeTab3 = new QLineEdit(tab_3);
        lineEditKernelSizeTab3->setObjectName(QStringLiteral("lineEditKernelSizeTab3"));

        horizontalLayout_25->addWidget(lineEditKernelSizeTab3);


        gridLayout_8->addLayout(horizontalLayout_25, 1, 0, 1, 1);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_40 = new QLabel(tab_3);
        label_40->setObjectName(QStringLiteral("label_40"));

        horizontalLayout_26->addWidget(label_40);

        lineEditMinimumVarianceTab3 = new QLineEdit(tab_3);
        lineEditMinimumVarianceTab3->setObjectName(QStringLiteral("lineEditMinimumVarianceTab3"));

        horizontalLayout_26->addWidget(lineEditMinimumVarianceTab3);

        label_26 = new QLabel(tab_3);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_26->addWidget(label_26);

        lineEditSamplingRadiusTab3 = new QLineEdit(tab_3);
        lineEditSamplingRadiusTab3->setObjectName(QStringLiteral("lineEditSamplingRadiusTab3"));

        horizontalLayout_26->addWidget(lineEditSamplingRadiusTab3);

        label_27 = new QLabel(tab_3);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayout_26->addWidget(label_27);

        lineEditNumberOfLevelsTab3 = new QLineEdit(tab_3);
        lineEditNumberOfLevelsTab3->setObjectName(QStringLiteral("lineEditNumberOfLevelsTab3"));

        horizontalLayout_26->addWidget(lineEditNumberOfLevelsTab3);

        label_31 = new QLabel(tab_3);
        label_31->setObjectName(QStringLiteral("label_31"));

        horizontalLayout_26->addWidget(label_31);

        comboBoxLevel0WeightTab3 = new QComboBox(tab_3);
        comboBoxLevel0WeightTab3->setObjectName(QStringLiteral("comboBoxLevel0WeightTab3"));

        horizontalLayout_26->addWidget(comboBoxLevel0WeightTab3);


        gridLayout_8->addLayout(horizontalLayout_26, 2, 0, 1, 1);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_33 = new QLabel(tab_3);
        label_33->setObjectName(QStringLiteral("label_33"));

        horizontalLayout_27->addWidget(label_33);

        lineEditDistanceHistogramNumberOfLevelsTab3 = new QLineEdit(tab_3);
        lineEditDistanceHistogramNumberOfLevelsTab3->setObjectName(QStringLiteral("lineEditDistanceHistogramNumberOfLevelsTab3"));

        horizontalLayout_27->addWidget(lineEditDistanceHistogramNumberOfLevelsTab3);

        label_39 = new QLabel(tab_3);
        label_39->setObjectName(QStringLiteral("label_39"));

        horizontalLayout_27->addWidget(label_39);

        lineEditDistanceHistogramLevelStepTab3 = new QLineEdit(tab_3);
        lineEditDistanceHistogramLevelStepTab3->setObjectName(QStringLiteral("lineEditDistanceHistogramLevelStepTab3"));

        horizontalLayout_27->addWidget(lineEditDistanceHistogramLevelStepTab3);

        label_36 = new QLabel(tab_3);
        label_36->setObjectName(QStringLiteral("label_36"));

        horizontalLayout_27->addWidget(label_36);

        lineEditNumberOfClusters = new QLineEdit(tab_3);
        lineEditNumberOfClusters->setObjectName(QStringLiteral("lineEditNumberOfClusters"));

        horizontalLayout_27->addWidget(lineEditNumberOfClusters);

        checkBoxNumberOfPointsTab3 = new QCheckBox(tab_3);
        checkBoxNumberOfPointsTab3->setObjectName(QStringLiteral("checkBoxNumberOfPointsTab3"));
        checkBoxNumberOfPointsTab3->setChecked(true);

        horizontalLayout_27->addWidget(checkBoxNumberOfPointsTab3);

        lineEditNumberOfPointsTab3 = new QLineEdit(tab_3);
        lineEditNumberOfPointsTab3->setObjectName(QStringLiteral("lineEditNumberOfPointsTab3"));

        horizontalLayout_27->addWidget(lineEditNumberOfPointsTab3);


        gridLayout_8->addLayout(horizontalLayout_27, 3, 0, 1, 1);


        gridLayout->addLayout(gridLayout_8, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QStringLiteral("horizontalLayout_39"));
        label_45 = new QLabel(tab_3);
        label_45->setObjectName(QStringLiteral("label_45"));

        horizontalLayout_39->addWidget(label_45);

        labelInitiateAllProgress = new QLabel(tab_3);
        labelInitiateAllProgress->setObjectName(QStringLiteral("labelInitiateAllProgress"));

        horizontalLayout_39->addWidget(labelInitiateAllProgress);

        horizontalLayout_39->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_39, 2, 0, 1, 1);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setObjectName(QStringLiteral("horizontalLayout_41"));
        label_46 = new QLabel(tab_3);
        label_46->setObjectName(QStringLiteral("label_46"));

        horizontalLayout_41->addWidget(label_46);

        lineEditPersistencePath = new QLineEdit(tab_3);
        lineEditPersistencePath->setObjectName(QStringLiteral("lineEditPersistencePath"));

        horizontalLayout_41->addWidget(lineEditPersistencePath);

        pushButtonPersistencePath = new QPushButton(tab_3);
        pushButtonPersistencePath->setObjectName(QStringLiteral("pushButtonPersistencePath"));

        horizontalLayout_41->addWidget(pushButtonPersistencePath);


        gridLayout->addLayout(horizontalLayout_41, 3, 0, 1, 1);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName(QStringLiteral("horizontalLayout_40"));
        label_44 = new QLabel(tab_3);
        label_44->setObjectName(QStringLiteral("label_44"));

        horizontalLayout_40->addWidget(label_44);

        lineEditResultsStoragePathTab5 = new QLineEdit(tab_3);
        lineEditResultsStoragePathTab5->setObjectName(QStringLiteral("lineEditResultsStoragePathTab5"));

        horizontalLayout_40->addWidget(lineEditResultsStoragePathTab5);

        pushButtonChooseResultsStoragePathTab5 = new QPushButton(tab_3);
        pushButtonChooseResultsStoragePathTab5->setObjectName(QStringLiteral("pushButtonChooseResultsStoragePathTab5"));

        horizontalLayout_40->addWidget(pushButtonChooseResultsStoragePathTab5);


        gridLayout->addLayout(horizontalLayout_40, 4, 0, 1, 1);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QStringLiteral("horizontalLayout_37"));
        label_42 = new QLabel(tab_3);
        label_42->setObjectName(QStringLiteral("label_42"));

        horizontalLayout_37->addWidget(label_42);

        lineEditTrainPath = new QLineEdit(tab_3);
        lineEditTrainPath->setObjectName(QStringLiteral("lineEditTrainPath"));

        horizontalLayout_37->addWidget(lineEditTrainPath);

        pushButtonTrainPath = new QPushButton(tab_3);
        pushButtonTrainPath->setObjectName(QStringLiteral("pushButtonTrainPath"));

        horizontalLayout_37->addWidget(pushButtonTrainPath);


        gridLayout->addLayout(horizontalLayout_37, 5, 0, 1, 1);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QStringLiteral("horizontalLayout_36"));
        label_43 = new QLabel(tab_3);
        label_43->setObjectName(QStringLiteral("label_43"));

        horizontalLayout_36->addWidget(label_43);

        lineEditTestPath = new QLineEdit(tab_3);
        lineEditTestPath->setObjectName(QStringLiteral("lineEditTestPath"));

        horizontalLayout_36->addWidget(lineEditTestPath);

        pushButtonTestPath = new QPushButton(tab_3);
        pushButtonTestPath->setObjectName(QStringLiteral("pushButtonTestPath"));

        horizontalLayout_36->addWidget(pushButtonTestPath);


        gridLayout->addLayout(horizontalLayout_36, 6, 0, 1, 1);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName(QStringLiteral("horizontalLayout_38"));
        label_37 = new QLabel(tab_3);
        label_37->setObjectName(QStringLiteral("label_37"));

        horizontalLayout_38->addWidget(label_37);

        comboBoxHistogramComparisonMethodTab4 = new QComboBox(tab_3);
        comboBoxHistogramComparisonMethodTab4->setObjectName(QStringLiteral("comboBoxHistogramComparisonMethodTab4"));

        horizontalLayout_38->addWidget(comboBoxHistogramComparisonMethodTab4);

        checkBoxLoadFromPersistence = new QCheckBox(tab_3);
        checkBoxLoadFromPersistence->setObjectName(QStringLiteral("checkBoxLoadFromPersistence"));

        horizontalLayout_38->addWidget(checkBoxLoadFromPersistence);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer);

        pushButtonSummarizeResults = new QPushButton(tab_3);
        pushButtonSummarizeResults->setObjectName(QStringLiteral("pushButtonSummarizeResults"));

        horizontalLayout_38->addWidget(pushButtonSummarizeResults);

        pushButtonInitiateProcess = new QPushButton(tab_3);
        pushButtonInitiateProcess->setObjectName(QStringLiteral("pushButtonInitiateProcess"));

        horizontalLayout_38->addWidget(pushButtonInitiateProcess);


        gridLayout->addLayout(horizontalLayout_38, 7, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_12->addWidget(tabWidget);

        RadialDescriptorGUIClass->setCentralWidget(centralWidget);

        retranslateUi(RadialDescriptorGUIClass);

        tabWidget->setCurrentIndex(0);
        comboBoxHistogramComparisonMethodTab4->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(RadialDescriptorGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *RadialDescriptorGUIClass)
    {
        RadialDescriptorGUIClass->setWindowTitle(QApplication::translate("RadialDescriptorGUIClass", "RadialDescriptor 0.8", 0));
        checkBoxBackgroundColorTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "Background Color:", 0));
        label_17->setText(QApplication::translate("RadialDescriptorGUIClass", "Sampling Radius:", 0));
        lineEditAllPointsSamplingSamplingRadius->setText(QApplication::translate("RadialDescriptorGUIClass", "2", 0));
        label_18->setText(QApplication::translate("RadialDescriptorGUIClass", "Number of Levels:", 0));
        lineEditAllPointsNumberOfLevels->setText(QApplication::translate("RadialDescriptorGUIClass", "4", 0));
        label_19->setText(QApplication::translate("RadialDescriptorGUIClass", "Level 0 Weight:", 0));
        comboBoxPointInAllPointsInterpolationWeight->clear();
        comboBoxPointInAllPointsInterpolationWeight->insertItems(0, QStringList()
         << QApplication::translate("RadialDescriptorGUIClass", "-1", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "0.5", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "0.3334", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "0.25", 0)
        );
        checkBoxMinDistanceTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "Min Distance:", 0));
        lineEditMinimumDistanceBetweenTwoPointsTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "3", 0));
        label_32->setText(QApplication::translate("RadialDescriptorGUIClass", "Image Blur:", 0));
        lineEditImageBlurTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "1", 0));
        label_35->setText(QApplication::translate("RadialDescriptorGUIClass", "Kernel:", 0));
        lineEditKernelSizeTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "3", 0));
        label_40->setText(QApplication::translate("RadialDescriptorGUIClass", "Min Variance:", 0));
        lineEditMinimumVarianceTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "5", 0));
        label_26->setText(QApplication::translate("RadialDescriptorGUIClass", "Signal Radius:", 0));
        lineEditSamplingRadiusTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "3", 0));
        label_27->setText(QApplication::translate("RadialDescriptorGUIClass", "Signal Levels:", 0));
        lineEditNumberOfLevelsTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "3", 0));
        label_31->setText(QApplication::translate("RadialDescriptorGUIClass", "Weight:", 0));
        comboBoxLevel0WeightTab3->clear();
        comboBoxLevel0WeightTab3->insertItems(0, QStringList()
         << QApplication::translate("RadialDescriptorGUIClass", "-1", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "0.5", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "0.3334", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "0.25", 0)
        );
        label_33->setText(QApplication::translate("RadialDescriptorGUIClass", "Number Of Levels:", 0));
        lineEditDistanceHistogramNumberOfLevelsTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "10", 0));
        label_39->setText(QApplication::translate("RadialDescriptorGUIClass", "Level Radius: %", 0));
        lineEditDistanceHistogramLevelStepTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "4", 0));
        label_36->setText(QApplication::translate("RadialDescriptorGUIClass", "Clusters:", 0));
        lineEditNumberOfClusters->setText(QApplication::translate("RadialDescriptorGUIClass", "19", 0));
        checkBoxNumberOfPointsTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "Points:", 0));
        lineEditNumberOfPointsTab3->setText(QApplication::translate("RadialDescriptorGUIClass", "200", 0));
        label_45->setText(QApplication::translate("RadialDescriptorGUIClass", "Progress:", 0));
        labelInitiateAllProgress->setText(QString());
        label_46->setText(QApplication::translate("RadialDescriptorGUIClass", "Persistence Path:", 0));
        lineEditPersistencePath->setText(QApplication::translate("RadialDescriptorGUIClass", "D:/majeek/hd2set/books/tests/68WordPartsAll/small/persistence", 0));
        pushButtonPersistencePath->setText(QApplication::translate("RadialDescriptorGUIClass", "Choose Persistence Path", 0));
        label_44->setText(QApplication::translate("RadialDescriptorGUIClass", "Results Storage Path:", 0));
        lineEditResultsStoragePathTab5->setText(QApplication::translate("RadialDescriptorGUIClass", "D:/majeek/hd2set/books/tests/68WordPartsAll/small/results", 0));
        pushButtonChooseResultsStoragePathTab5->setText(QApplication::translate("RadialDescriptorGUIClass", "Choose Results Path", 0));
        label_42->setText(QApplication::translate("RadialDescriptorGUIClass", "Train Path:", 0));
        lineEditTrainPath->setText(QApplication::translate("RadialDescriptorGUIClass", "D:/majeek/hd2set/books/tests/68WordPartsAll/small/train", 0));
        pushButtonTrainPath->setText(QApplication::translate("RadialDescriptorGUIClass", "Choose Train Path", 0));
        label_43->setText(QApplication::translate("RadialDescriptorGUIClass", "Test Path:", 0));
        lineEditTestPath->setText(QApplication::translate("RadialDescriptorGUIClass", "D:/majeek/hd2set/books/tests/68WordPartsAll/small/test", 0));
        pushButtonTestPath->setText(QApplication::translate("RadialDescriptorGUIClass", "Choose Test Path", 0));
        label_37->setText(QApplication::translate("RadialDescriptorGUIClass", "Comparison Method:", 0));
        comboBoxHistogramComparisonMethodTab4->clear();
        comboBoxHistogramComparisonMethodTab4->insertItems(0, QStringList()
         << QApplication::translate("RadialDescriptorGUIClass", "Cosine", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "Chi-Squared", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "Euclidean", 0)
         << QApplication::translate("RadialDescriptorGUIClass", "All", 0)
        );
        checkBoxLoadFromPersistence->setText(QApplication::translate("RadialDescriptorGUIClass", "Load From Persistence", 0));
        pushButtonSummarizeResults->setText(QApplication::translate("RadialDescriptorGUIClass", "Summarize", 0));
        pushButtonInitiateProcess->setText(QApplication::translate("RadialDescriptorGUIClass", "Initiate Process", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("RadialDescriptorGUIClass", "Evaluation", 0));
    } // retranslateUi

};

namespace Ui {
    class RadialDescriptorGUIClass: public Ui_RadialDescriptorGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIALDESCRIPTORQT5_H
