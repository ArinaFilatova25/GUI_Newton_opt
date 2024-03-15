#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , eps(0.001)
    , max_num_of_iter(100)
    , p(0.4)
    , delta(0.6)
    , alpha(0.3)
    , box(2)
    , x_0(2)
{
    x_0 = {0, 0};
    box = {{-2, 4}, {-2, 4}};
    f = function::f_1;
    m = method::newton;
    ns = nstop::grad_f;
    rs = rstop::max_iter;

    ui->setupUi(this);
    setWindowTitle("Settings");
    this->setFixedSize(894, 521);

    ui->func->setCurrentIndex(0);
    ui->crit_newton->setCurrentIndex(0);
    ui->crit_random->setCurrentIndex(0);

    ui->newton->click();

    ui->eps->setText(QString::number(eps));
    ui->max_iter->setText(QString::number(max_num_of_iter));
    ui->prob->setText(QString::number(p));
    ui->delta->setText(QString::number(delta));
    ui->alpha->setText(QString::number(alpha));
    ui->min_x->setText(QString::number(box[0].first));
    ui->min_y->setText(QString::number(box[1].first));
    ui->max_x->setText(QString::number(box[0].second));
    ui->max_y->setText(QString::number(box[1].second));
    ui->start_point_x->setText(QString::number(x_0[0]));
    ui->start_point_y->setText(QString::number(x_0[1]));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    f = static_cast<function>(ui->func->currentIndex());

    m = static_cast<method>(ui->newton->isChecked() ? method::newton : method::random);

    ns = static_cast<nstop>(ui->crit_newton->currentIndex());

    rs = static_cast<rstop>(ui->crit_random->currentIndex());

    double min_x = ui->min_x->text().toDouble();
    double min_y = ui->min_y->text().toDouble();
    double max_x = ui->max_x->text().toDouble();
    double max_y = ui->max_y->text().toDouble();
    box = {{min_x, max_x}, {min_y, max_y}};

    bool isValid = true;

    double start_point_x = ui->start_point_x->text().toDouble();
    double start_point_y = ui->start_point_y->text().toDouble();
    if (start_point_x < box[0].first || start_point_x > box[0].second ||
        start_point_y < box[1].first || start_point_y > box[1].second) {
        isValid = false;
        QMessageBox::critical(this, "Ошибка", "Начальная точка должна лежать в заданной области.");
    }

    double eps = ui->eps->text().toDouble();
    double p = ui->prob->text().toDouble();
    double delta = ui->delta->text().toDouble();
    double alpha = ui->alpha->text().toDouble();
    if (eps <= 0 || eps >= 1 ||
        p <= 0 || p >= 1 ||
        delta <= 0 || delta >= 1 ||
        alpha <= 0 || alpha >= 1) {
        isValid = false;
        QMessageBox::critical(this, "Ошибка", "Значения eps, p, delta, alpha должны быть от 0 до 1.");
    }

    int max_iter = ui->max_iter->text().toInt();
    if (max_iter <= 0 || max_iter >= 10000) {
        isValid = false;
        QMessageBox::critical(this, "Ошибка", "Значение max_iter должно быть больше 0 и меньше 10000.");
    }

    if (isValid) {
        this->x_0 = {start_point_x, start_point_y};
        this->eps = eps;
        this->max_num_of_iter = max_iter;
        this->p = p;
        this->delta = delta;
        this->alpha = alpha;
    }
}


void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);
    if (stdButton == QDialogButtonBox::Ok) {
        accept();
    } else if (stdButton == QDialogButtonBox::Cancel) {
        reject();

        ui->func->setCurrentIndex(0);
        ui->crit_newton->setCurrentIndex(0);
        ui->crit_random->setCurrentIndex(0);
        ui->eps->setText("0.001");
        ui->max_iter->setText("100");
        ui->prob->setText("0.4");
        ui->delta->setText("0.6");
        ui->alpha->setText("0.3");
        ui->min_x->setText("-2");
        ui->min_y->setText("-2");
        ui->max_x->setText("4");
        ui->max_y->setText("4");
        ui->start_point_x->setText("0");
        ui->start_point_y->setText("0");

        ui->newton->setChecked(true);
        ui->random->setChecked(false);
    }
}
