#include "Newton_opt.h"

Newton_opt::Newton_opt(){}

Newton_opt::~Newton_opt() {}

Newton_opt::Newton_opt(Function* function, std::vector<double> x_0, Area area,
    Stop_criterion* stop_criterion) : Optimization_method(function, x_0, area, stop_criterion) {
}

void Newton_opt::optimization() {
    int dim = function->get_dim();
    double eps = stop_criterion->get_eps();

    while (!stop_criterion->termination(this)) {
        std::vector<std::vector<double>> hess = function->hessian(seq_x_i.back(), eps / 10, area);
        
        Eigen::MatrixXd hessian_matrix(dim, dim);
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                hessian_matrix(i, j) = hess[i][j];
            }
        }

        Eigen::MatrixXd inverse_hessian_matrix = hessian_matrix.inverse();

        std::vector<double> grad = function->gradient(seq_x_i.back(), eps / 10, area);

        Eigen::VectorXd grad_vector(dim);
        for (int i = 0; i < dim; i++) {
            grad_vector(i) = grad[i];
        }

        Eigen::VectorXd hess_times_grad = inverse_hessian_matrix * grad_vector;

       
        std::vector<double> p(dim, 0);
        for (int i = 0; i < dim; ++i) {
            p[i] = -hess_times_grad(i);
        }

        double alpha = 1.0;
        double beta = 0.5;

        while (true) {
            std::vector<double> new_x = seq_x_i.back();
            for (int i = 0; i < dim; ++i) {
                new_x[i] += alpha * p[i];
            }

            double new_f_x = function->calculate(new_x);

            if (new_f_x <= seq_f_i.back()) {

                if (area.is_inside(new_x)) {
                    seq_x_i.push_back(new_x);
                    seq_f_i.push_back(new_f_x);
                    ++num_of_iter;
                    ++num_of_iter_since_last_approx;
                    break;
                }
            }

            alpha *= beta;
        }
    }
}
