#pragma once

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_CHAPMAN)) && __has_include("chapman.hpp")
namespace mech_chapman {
#include "chapman.hpp"
}
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_GOCART)) && __has_include("gocart.hpp")
namespace mech_gocart {
#include "gocart.hpp"
}
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SAPRC99)) && __has_include("saprc99.hpp")
namespace mech_saprc99 {
#include "saprc99.hpp"
}
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_TS1)) && __has_include("ts1.hpp")
namespace mech_ts1 {
#include "ts1.hpp"
}
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_CARBON)) && __has_include("carbon.hpp")
namespace mech_carbon {
#include "carbon.hpp"
}
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SMALL_STRATO)) && __has_include("small_strato.hpp")
namespace mech_small_strato {
#include "small_strato.hpp"
}
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SAPRCNOV)) && __has_include("saprcnov.hpp")
namespace mech_saprcnov {
#include "saprcnov.hpp"
}
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SAPRC99_MINI)) && __has_include("saprc99_mini.hpp")
namespace mech_saprc99_mini {
#include "saprc99_mini.hpp"
}
#endif
