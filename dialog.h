#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    enum function {
        f_1,
        f_2,
        f_3
    };

    enum method {
        newton,
        random
    };

    enum nstop{
        grad_f,
        x_diff,
        f_diff

    };

    enum rstop{
        f_diff_min,
        max_iter,
        iter_last_approx,
    };

    function get_function() const { return f; }
    method get_method() const { return m; }
    nstop get_nstop() const { return ns; }
    rstop get_rstop() const { return rs; }
    std::vector<double> get_start_point() const { return x_0; }
    std::vector<std::pair<double, double>> get_box() const { return box; }
    double get_eps() const { return eps; }
    int get_max_iter() const { return max_num_of_iter; }
    double get_alpha() const { return alpha; }
    double get_delta() const { return delta; }
    double get_p() const { return p; }

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;

    function f;
    method m;
    nstop ns;
    rstop rs;

    std::vector<double> x_0;
    std::vector<std::pair<double, double>> box;

    double eps;
    int max_num_of_iter;

    double alpha;
    double delta;
    double p;
};

#endif // DIALOG_H
