/**
 * @file test_c_abi.cpp
 * @brief Contract integration test suite for C ABI (`mkpp.h`)
 */

#include <gtest/gtest.h>
#include "mkpp.h"
#include <vector>

TEST(C_ABI, HandleLifecycleAndErrorHandling) {
    mkpp_handle_t handle = nullptr;

    // Test null handle error
    EXPECT_EQ(mkpp_initialize(handle), MKPP_ERROR_NULL_POINTER);

    // Test valid creation
    EXPECT_EQ(mkpp_create_handle(&handle, 10), MKPP_SUCCESS);
    EXPECT_NE(handle, nullptr);

    // Test initialization
    EXPECT_EQ(mkpp_initialize(handle), MKPP_SUCCESS);

    // Test metadata
    size_t count = 0;
    EXPECT_EQ(mkpp_get_species_count(handle, &count), MKPP_SUCCESS);
    EXPECT_EQ(count, static_cast<size_t>(MKPP_NUM_SPECIES));

    // Test destruction
    EXPECT_EQ(mkpp_destroy_handle(handle), MKPP_SUCCESS);
}

TEST(C_ABI, StateBindingValidation) {
    mkpp_handle_t handle = nullptr;
    ASSERT_EQ(mkpp_create_handle(&handle, 5), MKPP_SUCCESS);
    ASSERT_EQ(mkpp_initialize(handle), MKPP_SUCCESS);

    size_t num_cells = 5;
    size_t num_species = MKPP_NUM_SPECIES;

    std::vector<double> conc(num_cells * num_species, 1.0e-9);
    std::vector<double> temp(num_cells, 298.15);
    std::vector<double> pres(num_cells, 101325.0);
    std::vector<double> rho(num_cells, 2.45e19);

    // Null pointer state check
    EXPECT_EQ(mkpp_set_state_ptrs(handle, nullptr, temp.data(), pres.data(), rho.data()), MKPP_ERROR_NULL_POINTER);

    // Valid pointer binding
    EXPECT_EQ(mkpp_set_state_ptrs(handle, conc.data(), temp.data(), pres.data(), rho.data()), MKPP_SUCCESS);

    mkpp_destroy_handle(handle);
}

TEST(C_ABI, BatchMultiCellPhotolysisBinding) {
    size_t num_cells = 100;
    mkpp_handle_t handle = nullptr;
    ASSERT_EQ(mkpp_create_handle(&handle, num_cells), MKPP_SUCCESS);
    ASSERT_EQ(mkpp_initialize(handle), MKPP_SUCCESS);

    size_t num_species = MKPP_NUM_SPECIES;
    size_t num_photo = MKPP_NUM_PHOTOLYSIS > 0 ? MKPP_NUM_PHOTOLYSIS : 1;

    std::vector<double> conc(num_cells * num_species, 1.0e-9);
    std::vector<double> temp(num_cells, 298.15);
    std::vector<double> pres(num_cells, 101325.0);
    std::vector<double> rho(num_cells, 2.45e19);
    std::vector<double> photo(num_cells * num_photo, 1.0e-5);

    EXPECT_EQ(mkpp_set_state_ptrs(handle, conc.data(), temp.data(), pres.data(), rho.data()), MKPP_SUCCESS);
    EXPECT_EQ(mkpp_set_photolysis_ptrs(handle, photo.data()), MKPP_SUCCESS);

    mkpp_destroy_handle(handle);
}
