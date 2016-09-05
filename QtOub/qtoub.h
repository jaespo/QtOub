#ifndef QTOUB_H
#define QTOUB_H

#include <QtWidgets/QMainWindow>
#include "ui_qtoub.h"

class QtOub : public QMainWindow
{
	Q_OBJECT

private slots:
	void on_pushButton_logon_clicked();

public:
	QtOub(QWidget *parent = 0);
	~QtOub();

private:
	Ui::QtOubClass ui;
};

#endif // QTOUB_H
