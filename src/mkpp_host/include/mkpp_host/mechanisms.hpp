#pragma once

// Generated mechanisms own their namespace.  These aliases retain the host
// facade's stable spelling without wrapping includes in a second namespace.
#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_CHAPMAN)) && __has_include("chapman.hpp")
#include "chapman.hpp"
namespace mech_chapman { namespace mkpp = ::mkpp::generated::chapman; }
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_GOCART)) && __has_include("gocart.hpp")
#include "gocart.hpp"
namespace mech_gocart { namespace mkpp = ::mkpp::generated::gocart; }
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SAPRC99)) && __has_include("saprc99.hpp")
#include "saprc99.hpp"
namespace mech_saprc99 { namespace mkpp = ::mkpp::generated::saprc99; }
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_TS1)) && __has_include("ts1.hpp")
#include "ts1.hpp"
namespace mech_ts1 { namespace mkpp = ::mkpp::generated::ts1; }
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_CARBON)) && __has_include("carbon.hpp")
#include "carbon.hpp"
namespace mech_carbon { namespace mkpp = ::mkpp::generated::carbon; }
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SMALL_STRATO)) && __has_include("small_strato.hpp")
#include "small_strato.hpp"
namespace mech_small_strato { namespace mkpp = ::mkpp::generated::small_strato; }
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SAPRCNOV)) && __has_include("saprcnov.hpp")
#include "saprcnov.hpp"
namespace mech_saprcnov { namespace mkpp = ::mkpp::generated::saprcnov; }
#endif

#if (!defined(MKPP_HOST_SELECTED_MECHANISMS) || defined(MKPP_HOST_MECH_SAPRC99_MINI)) && __has_include("saprc99_mini.hpp")
#include "saprc99_mini.hpp"
namespace mech_saprc99_mini { namespace mkpp = ::mkpp::generated::saprc99_mini; }
#endif
