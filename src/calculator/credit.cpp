#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  Credit::setFixedSize(1700, 900);

  ui->setupUi(this);
  QPixmap back_img(":/img/img_2/3p.jpg");
  int w_cent = ui->back_img->width();
  int h_cent = ui->back_img->height();

  ui->back_img->setPixmap(back_img.scaled(w_cent, h_cent, Qt::KeepAspectRatio));

  QPixmap type(":/img/img_2/type.png");
  int w_type = ui->type->width();
  int h_type = ui->type->height();

  ui->type->setPixmap(type.scaled(w_type, h_type, Qt::KeepAspectRatio));

  QPixmap cred(":/img/img_2/credit).png");
  int w_cred = ui->hihi_credit->width();
  int h_cred = ui->hihi_credit->height();
  ui->hihi_credit->setPixmap(cred.scaled(w_cred, h_cred, Qt::KeepAspectRatio));

  QPixmap amount(":/img/img_2/cred_am.png");
  int w_amount = ui->amount->width();
  int h_amount = ui->amount->height();

  ui->amount->setPixmap(amount.scaled(w_amount, h_amount, Qt::KeepAspectRatio));

  QPixmap term(":/img/img_2/term.png");
  int w_term = ui->term->width();
  int h_term = ui->term->height();

  ui->term->setPixmap(term.scaled(w_term, h_term, Qt::KeepAspectRatio));

  QPixmap rate(":/img/img_2/rate.png");
  int w_rate = ui->rate->width();
  int h_rate = ui->rate->height();

  ui->rate->setPixmap(rate.scaled(w_rate, h_rate, Qt::KeepAspectRatio));

  QPixmap total(":/img/img_2/total.png");
  int w_total = ui->total->width();
  int h_total = ui->total->height();

  ui->total->setPixmap(total.scaled(w_total, h_total, Qt::KeepAspectRatio));

  QPixmap res(":/img/img_2/res.png");
  int w_res = ui->result->width();
  int h_res = ui->result->height();

  ui->result->setPixmap(res.scaled(w_res, h_res, Qt::KeepAspectRatio));

  QPixmap month(":/img/img_2/month.png");
  int w_month = ui->month->width();
  int h_month = ui->month->height();

  ui->month->setPixmap(month.scaled(w_month, h_month, Qt::KeepAspectRatio));

  QPixmap over(":/img/img_2/over.png");
  int w_over = ui->over->width();
  int h_over = ui->over->height();

  ui->over->setPixmap(over.scaled(w_over, h_over, Qt::KeepAspectRatio));
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_win_clicked() {
  this->close();        // Закрываем окно
  emit secondWindow();  // И вызываем сигнал на открытие главного окна
}

void Credit::on_calculate_clicked() {
  std::string str_sum = ui->am_numb->text().toStdString();
  char *sum = &str_sum[0];
  std::string str_month = ui->term_2->text().toStdString();
  char *month = &str_month[0];
  std::string str_procent = ui->rate_num->text().toStdString();
  char *procent = &str_procent[0];

  double overpayment = 0;
  double totalSum = 0;
  double sums = atof(sum);
  double months = atoi(month);
  double procents = (atof(procent) / 100) / 12;
  QString new_label = "";

  if (ui->differentiated->isChecked()) {
    double d = sums / months;
    double S = 0.0;
    int n = months;
    int numberMonth = n;

    for (int i = 0; i < n; i++) {
      S = differentiatedСredit(&sums, &months, &procents, &d);
      months--;
      QString num1 = QString::number(S, 'f', 2);
      QString qw = QString::number(numberMonth);
      totalSum = totalSum + S;
      new_label = new_label + num1 + " | " + qw + "month" + '\n';
      numberMonth--;
    }

    overpayment = totalSum - sums;
    QString num2 = QString::number(overpayment, 'f', 2);
    QString num3 = QString::number(totalSum, 'f', 2);

    ui->ii->setText(new_label);
    ui->over_l->setText(num2);
    ui->total_l->setText(num3);
  }
  if (ui->annuity->isChecked()) {
    sums = annuityСredit(&sums, &months, &procents, &overpayment, &totalSum);

    QString num1 = "\n\n" + QString::number(sums, 'f', 2);
    QString num2 = QString::number(overpayment, 'f', 2);
    QString num3 = QString::number(totalSum, 'f', 2);

    ui->ii->setText(num1);
    ui->over_l->setText(num2);
    ui->total_l->setText(num3);
  }
}
