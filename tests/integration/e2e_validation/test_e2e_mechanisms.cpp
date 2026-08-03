#include <gtest/gtest.h>
#include <Kokkos_Core.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <cstdlib>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#include TOSTRING(MECH_HEADER)

using ExecSpace = Kokkos::DefaultExecutionSpace;

#include "mkpp_host/dispatcher.hpp"

TEST(E2ESolverValidation, MechanismIntegration) {
    int cells = 1;
    if (const char* env_c = std::getenv("NUM_CELLS")) {
        cells = std::atoi(env_c);
    }
    int steps = 1;
    if (const char* env_s = std::getenv("NUM_STEPS")) {
        steps = std::atoi(env_s);
    }

    int n_spec = NUM_SPECIES_MACRO;
    if (n_spec == 0) n_spec = 100;

    std::vector<double> host_data(cells * n_spec * 1 * 1, 1.0e8);

    // Match initial concentrations from KPP def using exact MKPP species indices
    const double cfactor = 2.447600e+13;
    if (n_spec >= 79) {
        for (int i = 0; i < cells; ++i) {
            double* c = &host_data[i * n_spec];
            for (int k = 0; k < n_spec; ++k) c[k] = 0.0;
            c[ 2] = (0.1) * cfactor;       // NO
            c[ 3] = (0.05) * cfactor;      // NO2
            c[ 6] = (0.001) * cfactor;     // HONO
            c[ 9] = (0.05) * cfactor;      // SO2
            c[12] = (0.01121) * cfactor;   // HCHO
            c[13] = (0.002316) * cfactor;  // CCHO
            c[14] = (0.00172) * cfactor;   // RCHO
            c[15] = (0.00507) * cfactor;   // ACET
            c[16] = (0.00326) * cfactor;   // MEK
            c[17] = (0.000677) * cfactor;  // HCOOH
            c[18] = (0.00589) * cfactor;   // MEOH
            c[19] = (0.00116) * cfactor;   // CCO_OH
            c[20] = (0.000392) * cfactor;  // RCO_OH
            c[21] = (0.000121) * cfactor;  // GLY
            c[22] = (8.37e-05) * cfactor;  // MGLY
            c[24] = (0.00056) * cfactor;   // CRES
            c[25] = (7.51e-05) * cfactor;  // BALD
            c[26] = (8.93e-05) * cfactor;  // ISOPROD
            c[27] = (0.0013) * cfactor;    // METHACRO
            c[29] = (0.00193) * cfactor;   // PROD2
            c[33] = (0.0189) * cfactor;    // ETHENE
            c[34] = (0.000433) * cfactor;  // ISOPRENE
            c[35] = (0.01167) * cfactor;   // ALK1
            c[36] = (0.0188) * cfactor;    // ALK2
            c[37] = (0.0469) * cfactor;    // ALK3
            c[38] = (0.0417) * cfactor;    // ALK4
            c[39] = (0.0306) * cfactor;    // ALK5
            c[40] = (0.0118) * cfactor;    // ARO1
            c[41] = (0.00874) * cfactor;   // ARO2
            c[42] = (0.0104) * cfactor;    // OLE1
            c[43] = (0.00797) * cfactor;   // OLE2
            c[44] = (0.00082) * cfactor;   // TERP
            c[47] = (0.000606) * cfactor;  // PHEN
            c[56] = (0.2) * cfactor;       // XC
            c[57] = (7.843e-09) * cfactor; // O3P
            c[74] = (1000000.0) * cfactor; // AIR
            c[75] = (209000.0) * cfactor;  // O2
            c[76] = (20000.0) * cfactor;   // H2O
            c[78] = (1.0) * cfactor;       // CH4
        }
    }

    double dt_step = 60.0;
    if (const char* env_dt = std::getenv("DT_STEP")) {
        dt_step = std::atof(env_dt);
    }

    mkpp::concentrations_view_t state(host_data.data(), cells, n_spec, 1, 1);
    const bool use_serial_host = []() {
        const char* mode = std::getenv("MKPP_EXECUTION_MODE");
        return mode != nullptr && std::string(mode) == "serial";
    }();

    // Provide Cloud-J photolysis rates (jvals) for mechanisms with PHOTOLYSIS reactions.
    // For benchmark/validation purposes, use typical mid-day J-values (s^-1).
    std::vector<double> jvals_data(64, 0.0);
    // Representative SAPRC-99 J-values at SZA ~30 degrees (typical clear-sky noon):
    jvals_data[0] = 5.0e-6;   // NO2_IUPAC04
    jvals_data[1] = 5.0e-6;   // NO2 -> NO + O3P
    jvals_data[2] = 3.0e-5;   // O3 -> O3P
    jvals_data[3] = 3.0e-5;   // O3 -> O1D
    jvals_data[4] = 2.0e-4;   // HONO -> HO + NO
    jvals_data[5] = 2.0e-4;   // HONO alt
    jvals_data[6] = 6.0e-6;   // HNO3
    jvals_data[7] = 5.0e-5;   // HNO4
    jvals_data[8] = 1.0e-5;   // NO3 -> NO2
    jvals_data[9] = 3.0e-5;   // HCHO -> HO2 + CO
    jvals_data[10] = 4.0e-5;  // HCHO -> H2 + CO
    jvals_data[11] = 1.0e-5;  // CCHO
    jvals_data[12] = 5.0e-6;  // RCHO
    jvals_data[13] = 7.0e-6;  // ACET
    jvals_data[14] = 4.0e-6;  // MEK
    jvals_data[15] = 3.0e-6;  // COOH
    jvals_data[16] = 5.0e-5;  // GLY -> formaldehyde
    jvals_data[17] = 2.0e-5;  // GLY -> glyoxal
    jvals_data[18] = 1.0e-5;  // MGLY
    jvals_data[19] = 1.0e-5;  // BACL
    jvals_data[20] = 3.0e-6;  // BALD
    jvals_data[21] = 4.0e-6;  // AFG1
    jvals_data[22] = 3.0e-5;  // METHACRO
    jvals_data[23] = 2.0e-5;  // MVK
    jvals_data[24] = 3.0e-5;  // ISOPROD
    jvals_data[25] = 4.0e-5;  // PROD2
    jvals_data[26] = 1.0e-5;  // DCB1
    jvals_data[27] = 1.0e-5;  // IC3ONO2
    jvals_data[28] = 1.0e-5;  // HOCCHO
    const double* jvals = jvals_data.data();

    auto start = std::chrono::high_resolution_clock::now();
    if (use_serial_host) {
        mkpp::host::execute_mechanism_serial_steps<mkpp::SolverKernels<ExecSpace>>(state, dt_step, steps, jvals);
    } else {
        mkpp::host::execute_mechanism_steps<mkpp::SolverKernels<ExecSpace>>(TOSTRING(MECH_HEADER), state, dt_step, steps, jvals);
    }
    Kokkos::fence();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Execution mode: " << (use_serial_host ? "serial" : "kokkos") << "\n";
    std::cout << "Time: " << std::fixed << std::setprecision(2) << elapsed.count() << " ms\n";

    std::ofstream out("e2e_output.csv");
    out << "time_step,species_name,concentration\n";
    for(int k=0; k<n_spec; k++) {
        out << steps << "," << k << "," << std::scientific << std::setprecision(12) << host_data[k] << "\n";
    }
    out.close();
}

int main(int argc, char** argv) {
    Kokkos::initialize(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    Kokkos::finalize();
    return result;
}
