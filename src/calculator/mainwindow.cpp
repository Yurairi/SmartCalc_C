#include "mainwindow.h"

#include <QPixmap>

#include "qcustomplot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  MainWindow::setFixedSize(1700, 1080);
  ui->setupUi(this);

  sCredit = new Credit();
  connect(sCredit, &Credit::secondWindow, this, &MainWindow::show);

  player = new QMediaPlayer;
  out_a = new QAudioOutput;
  player->setAudioOutput(out_a);
  player->setSource(QUrl("qrc:/img/sounds/1234.mp3"));
  out_a->setVolume(300);
  player->play();

  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->xAxis->setRange(-20, 20);
  ui->widget->yAxis->setRange(-20, 20);

  QPixmap PLOT(":/img/img_2/PLOT_1.png");
  int w_plot = ui->PLOT->width();
  int h_plot = ui->PLOT->height();

  ui->PLOT->setPixmap(PLOT.scaled(w_plot, h_plot, Qt::KeepAspectRatio));

  QPixmap back_img(":/img/img_2/5677.png");
  int w_cent = ui->back_img->width();
  int h_cent = ui->back_img->height();

  ui->back_img->setPixmap(back_img.scaled(w_cent, h_cent, Qt::KeepAspectRatio));

  QPixmap MINE(":/img/img_2/text.png");
  ui->MINE->setPixmap(MINE.scaled(851, 141, Qt::KeepAspectRatio));

  QPixmap lab_x(":/img/img_2/lim_x.png");
  ui->label_x_lim->setPixmap(lab_x.scaled(161, 21, Qt::KeepAspectRatio));

  QPixmap lab_y(":/img/img_2/lim_y.png");
  ui->label_y_lim->setPixmap(lab_y.scaled(161, 21, Qt::KeepAspectRatio));

  QPixmap stp(":/img/img_2/step.png");
  ui->label_step->setPixmap(stp.scaled(161, 21, Qt::KeepAspectRatio));

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->replot();

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(delete_string()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this, SLOT(dot_cond()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_res, SIGNAL(clicked()), this, SLOT(pushString()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digit_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->String->text() + button->text();
  ui->String->setText(new_label);
}

void MainWindow::math_operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->String->text();
  bool end_with_mod = ui->String->text().endsWith("%");
  bool end_with_pow = ui->String->text().endsWith("^");
  bool end_with_minus = ui->String->text().endsWith("-");
  bool end_with_plus = ui->String->text().endsWith("+");
  bool end_with_mult = ui->String->text().endsWith("*");
  bool end_with_div = ui->String->text().endsWith("/");
  bool not_end_with_open = !ui->String->text().endsWith("(");
  bool prov = !end_with_mod && !end_with_pow && !end_with_minus &&
              !end_with_plus && !end_with_mult && !end_with_div;
  if (button->text() == "/" && prov && not_end_with_open) {
    new_label += "/";
  } else if (button->text() == "*" && prov && not_end_with_open) {
    new_label += "*";
  } else if (button->text() == "+" && prov) {
    new_label += "+";
  } else if (button->text() == "-" && prov) {
    new_label += "-";
  } else if (button->text() == "^" && prov && not_end_with_open) {
    new_label += "^";
  } else if (button->text() == "%" && prov && not_end_with_open) {
    new_label += "%";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")" && prov && not_end_with_open) {
    new_label += ")";
  }
  ui->String->setText(new_label);
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  ui->String->setText(ui->String->text() + button->text() + "(");
}

void MainWindow::delete_string() {
  ui->String->setText("");
  ui->String_plot->setText("");
}

void MainWindow::dot_cond() {
  if (!(ui->String->text().endsWith('.')))
    ui->String->setText(ui->String->text() + ".");
}

void MainWindow::pushString() {
  std::string str = ui->String->text().toStdString();
  char *expression = &str[0];
  std::string str_sum = ui->doubleSpinBox_x->text().toStdString();
  char *sum = &str_sum[0];
  double resX = atof(sum);
  double res_numb = 0.0;

  ui->String_plot->setText(ui->String->text());

  std::string str_x_min = ui->doubleSpinBox_x_min->text().toStdString();
  char *x_min_ = &str_x_min[0];
  double x_min = atof(x_min_);
  std::string str_x_max = ui->doubleSpinBox_x_max->text().toStdString();
  char *x_max_ = &str_x_max[0];
  double x_max = atof(x_max_);
  std::string str_y_min = ui->doubleSpinBox_y_min->text().toStdString();
  char *y_min_ = &str_y_min[0];
  double y_min = atof(y_min_);
  std::string str_y_max = ui->doubleSpinBox_y_max->text().toStdString();
  char *y_max_ = &str_y_max[0];
  double y_max = atof(y_max_);
  std::string str_h = ui->doubleSpinBox_h->text().toStdString();
  char *h_ = &str_h[0];
  h = atof(h_);

  QPen my_pen;
  my_pen.setColor(QColor(178, 7, 116));
  my_pen.setWidthF(2);
  xBegin = x_min;
  xEnd = x_max;
  x.clear();
  y.clear();

  N = (xEnd - xBegin) / h + 2;

  if (h && xBegin && xEnd) {
    for (X = xBegin; X <= xEnd; X += h) {
      if (expression[0]) Result_func(expression, &res_numb, X);
      if (res_numb <= y_max && res_numb >= y_min) {
        x.push_back(X);
        y.push_back(res_numb);
      }
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->graph(0)->setPen(my_pen);
    ui->widget->replot();
  }

  if (expression[0]) {
    int error = Result_func(expression, &res_numb, resX);
    QString num1;
    if (!error)
      num1 = QString::number(res_numb, 'f', 6);
    else
      num1 = "ERROR";
    ui->String->setText(num1);
  }
}

void MainWindow::on_pushButton_credit_cal_clicked() {
  sCredit->show();  // Показываем второе окно
  this->close();
}
