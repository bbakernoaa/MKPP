#pragma once

#include <Kokkos_Core.hpp>
#include "dispatcher.hpp"
#include "mechanisms.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace mkpp {
namespace host {

struct MechanismInfo {
    std::string name;
    int num_species{0};
    int num_reactions{0};
    bool requires_env{false};
};

class MechanismRegistry {
public:
    static std::vector<std::string> get_registered_mechanisms() {
        std::vector<std::string> list;
#if __has_include("chapman.hpp")
        list.push_back("chapman");
#endif
#if __has_include("gocart.hpp")
        list.push_back("gocart");
#endif
#if __has_include("saprc99.hpp")
        list.push_back("saprc99");
#endif
#if __has_include("ts1.hpp")
        list.push_back("ts1");
#endif
#if __has_include("carbon.hpp")
        list.push_back("carbon");
#endif
#if __has_include("small_strato.hpp")
        list.push_back("small_strato");
#endif
#if __has_include("saprcnov.hpp")
        list.push_back("saprcnov");
#endif
#if __has_include("saprc99_mini.hpp")
        list.push_back("saprc99_mini");
#endif
        return list;
    }

    static bool has_mechanism(const std::string& name) {
        auto list = get_registered_mechanisms();
        for (const auto& m : list) {
            if (m == name) return true;
        }
        return false;
    }

    static MechanismInfo get_info(const std::string& name) {
#if __has_include("chapman.hpp")
        if (name == "chapman") {
            return {"chapman", mech_chapman::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, false};
        }
#endif
#if __has_include("gocart.hpp")
        if (name == "gocart") {
            return {"gocart", mech_gocart::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, true};
        }
#endif
#if __has_include("saprc99.hpp")
        if (name == "saprc99") {
            return {"saprc99", mech_saprc99::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, false};
        }
#endif
#if __has_include("ts1.hpp")
        if (name == "ts1") {
            return {"ts1", mech_ts1::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, false};
        }
#endif
#if __has_include("carbon.hpp")
        if (name == "carbon") {
            return {"carbon", mech_carbon::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, false};
        }
#endif
#if __has_include("small_strato.hpp")
        if (name == "small_strato") {
            return {"small_strato", mech_small_strato::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, false};
        }
#endif
#if __has_include("saprcnov.hpp")
        if (name == "saprcnov") {
            return {"saprcnov", mech_saprcnov::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, false};
        }
#endif
#if __has_include("saprc99_mini.hpp")
        if (name == "saprc99_mini") {
            return {"saprc99_mini", mech_saprc99_mini::mkpp::SolverKernels<Kokkos::DefaultExecutionSpace>::NUM_SPECIES, 0, false};
        }
#endif
        std::string err = "FATAL ERROR: Unknown mechanism '" + name + "'. Supported: ";
        auto list = get_registered_mechanisms();
        for (size_t i = 0; i < list.size(); ++i) {
            err += list[i] + (i + 1 < list.size() ? ", " : "");
        }
        std::cerr << err << std::endl;
        throw std::runtime_error(err);
    }

    template <typename StateView>
    static void execute(const std::string& name, StateView state, const HostExecutionParams& params) {
        using ExecSpace = Kokkos::DefaultExecutionSpace;
        const int num_cells = static_cast<int>(state.extent(0));

#if __has_include("chapman.hpp")
        if (name == "chapman") {
            using SolverType = mech_chapman::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_chapman",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
#if __has_include("gocart.hpp")
        if (name == "gocart") {
            using SolverType = mech_gocart::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_gocart",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
#if __has_include("saprc99.hpp")
        if (name == "saprc99") {
            using SolverType = mech_saprc99::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_saprc99",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
#if __has_include("ts1.hpp")
        if (name == "ts1") {
            using SolverType = mech_ts1::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_ts1",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
#if __has_include("carbon.hpp")
        if (name == "carbon") {
            using SolverType = mech_carbon::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_carbon",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
#if __has_include("small_strato.hpp")
        if (name == "small_strato") {
            using SolverType = mech_small_strato::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_small_strato",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
#if __has_include("saprcnov.hpp")
        if (name == "saprcnov") {
            using SolverType = mech_saprcnov::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_saprcnov",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
#if __has_include("saprc99_mini.hpp")
        if (name == "saprc99_mini") {
            using SolverType = mech_saprc99_mini::mkpp::SolverKernels<ExecSpace>;
            Kokkos::parallel_for("MKPP_Dispatch_saprc99_mini",
                Kokkos::RangePolicy<ExecSpace>(0, num_cells, Kokkos::ChunkSize(64)),
                ParamsTiledCellIntegrator<SolverType, StateView>(state, params));
            Kokkos::fence();
            return;
        }
#endif
        std::string err = "FATAL ERROR: Unknown mechanism '" + name + "'. Supported: ";
        auto list = get_registered_mechanisms();
        for (size_t i = 0; i < list.size(); ++i) {
            err += list[i] + (i + 1 < list.size() ? ", " : "");
        }
        std::cerr << err << std::endl;
        throw std::runtime_error(err);
    }
};

} // namespace host
} // namespace mkpp
