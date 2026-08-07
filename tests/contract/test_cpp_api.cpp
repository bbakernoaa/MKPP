/**
 * @file test_cpp_api.cpp
 * @brief Contract integration test suite for idiomatic C++ wrapper (`mkpp.hpp`)
 */

#include <gtest/gtest.h>
#include "mkpp.hpp"
#include <vector>

TEST(CPP_API, ContextLifecycle) {
    mkpp::MechanismContext ctx(10);
    EXPECT_NO_THROW(ctx.initialize());

    EXPECT_GT(ctx.getSpeciesCount(), 0u);
    EXPECT_GE(ctx.getReactionCount(), 0u);
}

TEST(CPP_API, StatePointerBinding) {
    std::size_t num_cells = 5;
    mkpp::MechanismContext ctx(num_cells);
    ctx.initialize();

    std::size_t num_species = ctx.getSpeciesCount();
    std::vector<double> conc(num_cells * num_species, 1.0e-9);
    std::vector<double> temp(num_cells, 298.15);
    std::vector<double> pres(num_cells, 101325.0);
    std::vector<double> rho(num_cells, 2.45e19);

    EXPECT_NO_THROW(ctx.setStatePointers(conc.data(), temp.data(), pres.data(), rho.data()));
}

TEST(CPP_API, IndexLookupsAndMetadata) {
    mkpp::MechanismContext ctx(1);
    ctx.initialize();

    EXPECT_GE(ctx.getSpeciesIndex("O3"), 0);
    EXPECT_EQ(ctx.getSpeciesIndex("NON_EXISTENT_SPECIES"), -1);
}
