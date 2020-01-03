#ifndef QCEFVIEWTEST_H
#define QCEFVIEWTEST_H

#include "ui_qcefviewtest.h"
#include <QtWidgets/QMainWindow>

class QCefViewTest : public QMainWindow {
    Q_OBJECT

  public:
    QCefViewTest(QWidget *parent = 0);
    ~QCefViewTest();

  private:
    Ui::QCefViewTestClass ui;
};

#endif // QCEFVIEWTEST_H
