#include "gocart.hpp"
int main() {
    Kokkos::initialize();
    {
        double* dummy_ptr = new double[20 * 10 * 10 * 1];
        mkpp::concentrations_view_t view(dummy_ptr, 20, 10, 10, 1);
        delete[] dummy_ptr;
    }
    Kokkos::finalize();
    return 0;
}
