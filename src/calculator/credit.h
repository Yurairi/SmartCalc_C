#ifndef Credit_H
#define Credit_H

#include <QDialog>

extern "C" {
#include "calc_credit.h"
}

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 signals:
  void secondWindow();

 private slots:

  void on_pushButton_win_clicked();

  void on_calculate_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // Credit_H
