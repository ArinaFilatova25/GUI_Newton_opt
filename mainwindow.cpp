#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , eps(0.001)
    , max_num_of_iter(100)
    , p(0.4)
    , delta(0.6)
    , alpha(0.3)
    , box(2)
    , x_0(2)
    , f(new Function1())
    , optimization_method(new Newton_opt())
    , stop_criterion(new Criterion_grad_f())
    , scene(nullptr)
{
    x_0 = {0, 0};
    box = {{-2, 4}, {-2, 4}};

    ui->setupUi(this);

    setWindowTitle("Opimization");
    this->setFixedSize(800, 600);

    ui->func_min->setVisible(false);
    ui->min_point->setVisible(false);
    ui->num_iter->setVisible(false);
    ui->start_point->setVisible(false);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(&dial, &Dialog::accepted, this, &MainWindow::draw_function);
    connect(scene, &OptimizationScene::sceneClicked, this, &MainWindow::on_sceneClicked);

}

MainWindow::~MainWindow()
{
    delete scene;
    delete optimization_method;
    delete stop_criterion;
    delete f;
    delete ui;
}


void MainWindow::on_actionSettings_triggered()
{
    dial.exec();
    on_actionVisualization_triggered(dial.get_start_point());
}


void MainWindow::on_sceneClicked(const QPointF &point)
{

    int plot_width = ui->graphicsView->width();
    int plot_height = ui->graphicsView->height();

    double x_step = (box[0].second - box[0].first) / plot_width;
    double y_step = (box[1].second - box[1].first) / plot_height;

    double x = box[0].first + x_step * point.x();
    double y = box[1].second - y_step * point.y();

    if (Area(box).is_inside({x, y})) {
        std::vector<double> click_point = {x, y};
        on_actionVisualization_triggered(click_point);
    }
}

std::vector<std::vector<double>> MainWindow::calculate_function_values(Function& function,
                                                                     const std::vector<std::pair<double, double>>& box,
                                                                     int num_points_x, int num_points_y)
{
    std::vector<std::vector<double>> values(num_points_x, std::vector<double>(num_points_y, 0.0));

    double x_step = (box[0].second - box[0].first) / (num_points_x - 1);
    double y_step = (box[1].second - box[1].first) / (num_points_y - 1);

    for (int i = 0; i < num_points_x; ++i) {
        for (int j = 0; j < num_points_y; ++j) {
            double x = box[0].first + i * x_step;
            double y = box[1].first + j * y_step;
            values[i][j] = function.calculate({x, y});
        }
    }

    return values;
}


QColor MainWindow::map_value_to_color(double value, double min_value, double max_value)
{
    double ratio = (value - min_value) / (max_value - min_value);
    int red = static_cast<int>(255 * ratio);
    int blue = static_cast<int>(255 * (1 - ratio));
    return QColor(red, 0, blue);
}

void MainWindow::draw_function()
{
    if (scene) {
        delete scene;
    }
    scene = new OptimizationScene(this);
    ui->graphicsView->setScene(scene);

    connect(scene, &OptimizationScene::sceneClicked, this, &MainWindow::on_sceneClicked);

    Dialog::function selected_function = dial.get_function();
    std::vector<std::pair<double, double>> selected_box = dial.get_box();

    switch (selected_function) {
    case Dialog::function::f_1:
        f = new Function1();
        break;
    case Dialog::function::f_2:
        f = new Function2();
        break;
    case Dialog::function::f_3:
        f = new Function3();
        break;
    default:
        QMessageBox::critical(this, "Ошибка", "Неверно выбрана функция.");
        return;
    }

    std::vector<std::vector<double>> function_values = calculate_function_values(*f, selected_box, 100, 100);

    double min_value = std::numeric_limits<double>::max();
    double max_value = -std::numeric_limits<double>::max();
    for (const auto& row : function_values) {
        for (double value : row) {
            min_value = std::min(min_value, value);
            max_value = std::max(max_value, value);
        }
    }

    int plot_width = ui->graphicsView->width();
    int plot_height = ui->graphicsView->height();

    QPixmap pixmap(plot_width, plot_height);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    double x_step = qRound(static_cast<double>(pixmap.width()) / function_values.size());
    double y_step = qRound(static_cast<double>(pixmap.height()) / function_values[0].size());

    for (size_t i = 0; i < function_values.size(); ++i) {
        for (size_t j = 0; j < function_values[i].size(); ++j) {
            double value = function_values[i][j];
            QColor color = map_value_to_color(value, min_value, max_value);
            painter.fillRect(i * x_step, j * y_step, x_step, y_step, color);
        }
    }

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
    scene->addItem(pixmapItem);

}


void MainWindow::draw_trajectory()
{
    if (!trajectory.empty() && scene) {
        QPixmap trajectoryPixmap(801, 461);
        trajectoryPixmap.fill(Qt::transparent);

        QPainter painter(&trajectoryPixmap);
        QPen pen(Qt::green);
        pen.setWidth(2);
        painter.setPen(pen);

        double x_step = trajectoryPixmap.width() / (box[0].second - box[0].first);
        double y_step = trajectoryPixmap.height() / (box[1].second - box[1].first);


        for (size_t i = 1; i < trajectory.size(); ++i) {
            double x1 = (trajectory[i-1][0] - box[0].first) * x_step;
            double y1 = trajectoryPixmap.height() - (trajectory[i-1][1] - box[1].first) * y_step;
            double x2 = (trajectory[i][0] - box[0].first) * x_step;
            double y2 = trajectoryPixmap.height() - (trajectory[i][1] - box[1].first) * y_step;
            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }


        QGraphicsPixmapItem *trajectoryItem = new QGraphicsPixmapItem(trajectoryPixmap);
        scene->addItem(trajectoryItem);
    }
}


void MainWindow::on_actionVisualization_triggered(const std::vector<double> &start_point)
{
    if (f)
        delete f;

    Dialog::function selected_function = dial.get_function();
    switch (selected_function) {
    case Dialog::function::f_1:
        f = new Function1();
        break;
    case Dialog::function::f_2:
        f = new Function2();
        break;
    case Dialog::function::f_3:
        f = new Function3();
        break;
    default:
        QMessageBox::critical(this, "Ошибка", "Неверно выбрана функция.");
        return;
    }


     x_0 = start_point;


    switch (dial.get_method()) {
    case Dialog::method::newton:
        switch (dial.get_nstop()) {
        case Dialog::nstop::grad_f:
            stop_criterion = new Criterion_grad_f(dial.get_eps(), dial.get_max_iter());
            break;
        case Dialog::nstop::x_diff:
            stop_criterion = new Criterion_x_difference(dial.get_eps(), dial.get_max_iter());
            break;
        case Dialog::nstop::f_diff:
            stop_criterion = new Criterion_f_difference(dial.get_eps(), dial.get_max_iter());
            break;
        default:
            QMessageBox::critical(this, "Ошибка", "Неверно выбран критерий останова для метода Ньютона.");
            break;
        }
        optimization_method = new Newton_opt(f, x_0, Area(dial.get_box()), stop_criterion);
        break;
    case Dialog::method::random:
        switch (dial.get_rstop()) {
        case Dialog::rstop::f_diff_min:
            stop_criterion = new Criterion_f_difference_min(dial.get_eps(), dial.get_max_iter());
            break;
        case Dialog::rstop::max_iter:
            stop_criterion = new Criterion_max_iter(dial.get_max_iter());
            break;
        case Dialog::rstop::iter_last_approx:
            stop_criterion = new Criterion_num_iter_last_approx(dial.get_max_iter());
            break;
        default:
            QMessageBox::critical(this, "Ошибка", "Неверно выбран критерий останова для случайного поиска.");
            break;
        }
        optimization_method = new Random_search(f, x_0, Area(dial.get_box()), stop_criterion, dial.get_p(), dial.get_delta(), dial.get_alpha());
        break;
    default:
        QMessageBox::critical(this, "Ошибка", "Неверно выбран метод оптимизации.");
        break;
    }

    box = dial.get_box();

    optimization_method->optimization();

    trajectory = optimization_method->get_seq_x_i();

    draw_function();
    draw_trajectory();

    std::vector<double> min_point = optimization_method->get_seq_x_i().back();
    double min_value = optimization_method->get_seq_f_i().back();
    int num_iterations = optimization_method->get_num_of_iter();

    QString text_func_min = "Минимальное значение: " + QString::number(min_value);
    QString text_min_point = "Точка минимума: " + QString("(%1, %2)").arg(min_point[0]).arg(min_point[1]);
    QString text_num_iter = "Количество итераций: " + QString::number(num_iterations);
    QString text_start_point = "Начальная точка: " + QString("(%1, %2)").arg(start_point[0]).arg(start_point[1]);

    ui->func_min->setVisible(true);
    ui->min_point->setVisible(true);
    ui->num_iter->setVisible(true);
    ui->start_point->setVisible(true);

    ui->func_min->setText(text_func_min);
    ui->min_point->setText(text_min_point);
    ui->num_iter->setText(text_num_iter);
    ui->start_point->setText(text_start_point);

}


