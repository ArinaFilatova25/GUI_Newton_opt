#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

#include "Area.h"
#include "Function.h"
#include "Optimization_method.h"
#include "Stop_criterion.h"
#include "Newton_opt.h"
#include "Random_search.h"

#include <dialog.h>
#include "optimizationscene.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void draw_function();
    void draw_trajectory();
    QColor map_value_to_color(double value, double min_value, double max_value);

    std::vector<std::vector<double>> calculate_function_values(Function& function,
                                                             const std::vector<std::pair<double, double>>& box,
                                                             int num_points_x, int num_points_y);


private slots:
    void on_actionSettings_triggered();

    void on_sceneClicked(const QPointF &point);

    void on_actionVisualization_triggered(const std::vector<double> &start_point);

private:
    Ui::MainWindow *ui;

    Dialog dial;

    Function* f;
    std::vector<double> x_0;
    std::vector<std::pair<double, double>> box;

    Optimization_method* optimization_method;
    Stop_criterion* stop_criterion;

    double eps;
    int max_num_of_iter;

    double alpha;
    double delta;
    double p;

    std::vector<std::vector<double>> trajectory;

    OptimizationScene* scene;

};
#endif // MAINWINDOW_H
