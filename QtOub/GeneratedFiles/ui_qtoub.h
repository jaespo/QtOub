/********************************************************************************
** Form generated from reading UI file 'qtoub.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTOUB_H
#define UI_QTOUB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtOubClass
{
public:
    QWidget *myCentralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_user;
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *lineEdit_password;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtOubClass)
    {
        if (QtOubClass->objectName().isEmpty())
            QtOubClass->setObjectName(QStringLiteral("QtOubClass"));
        QtOubClass->resize(1091, 851);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtOubClass->sizePolicy().hasHeightForWidth());
        QtOubClass->setSizePolicy(sizePolicy);
        QtOubClass->setStyleSheet(QStringLiteral(""));
        myCentralWidget = new QWidget(QtOubClass);
        myCentralWidget->setObjectName(QStringLiteral("myCentralWidget"));
        myCentralWidget->setEnabled(true);
        myCentralWidget->setStyleSheet(QStringLiteral("#myCentralWidget {border-image: url(:/QtOub/LogonBackground.jpg) 0 0 0 0 stretch stretch; }"));
        gridLayout = new QGridLayout(myCentralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 0, 1, 1);

        groupBox = new QGroupBox(myCentralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(200, 111));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAutoFillBackground(true);
        groupBox->setStyleSheet(QStringLiteral(""));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_user = new QLineEdit(groupBox);
        lineEdit_user->setObjectName(QStringLiteral("lineEdit_user"));
        lineEdit_user->setEnabled(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_user);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, pushButton);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_password = new QLineEdit(groupBox);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEdit_password);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        QtOubClass->setCentralWidget(myCentralWidget);
        menuBar = new QMenuBar(QtOubClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1091, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        QtOubClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtOubClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtOubClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtOubClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtOubClass->setStatusBar(statusBar);
        QWidget::setTabOrder(lineEdit_user, lineEdit_password);
        QWidget::setTabOrder(lineEdit_password, pushButton);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(QtOubClass);
        QObject::connect(pushButton, SIGNAL(clicked()), QtOubClass, SLOT(on_pushButton_logon_clicked()));

        QMetaObject::connectSlotsByName(QtOubClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtOubClass)
    {
        QtOubClass->setWindowTitle(QApplication::translate("QtOubClass", "QtOub", 0));
        groupBox->setTitle(QApplication::translate("QtOubClass", "Logon", 0));
        label->setText(QApplication::translate("QtOubClass", "User", 0));
        pushButton->setText(QApplication::translate("QtOubClass", "Logon", 0));
        label_2->setText(QApplication::translate("QtOubClass", "Password", 0));
        menuFile->setTitle(QApplication::translate("QtOubClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class QtOubClass: public Ui_QtOubClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTOUB_H
