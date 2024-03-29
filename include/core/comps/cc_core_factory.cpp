#include "cc_core_factory.h"

#include <set>

#include "../../cc/cclog.h"
#include "cc_core_types.h"
#include "cc_discrete_distribution.h"
#include "cc_uniform_distribution.h"
#include "cc_mt19937.h"

namespace cc
{

	bool cc_core_factory::cc_contains_type(std::string type) const {

		std::string lcType = type;
		ToLower(lcType);

		static std::set<std::string> types = {
			cc_discrete_dist_type,
			cc_uniform_dist_type,
			cc_rng_type
		};

		return types.count(lcType) == 1;
	}

	cc_component* cc_core_factory::cc_create_component(const std::string& type, const std::string& name, cc_config* config) const {

		std::string lcType = type;
		ToLower(lcType);

		if (lcType == cc_discrete_dist_type) {
			cc_discrete_distribution* ret = new cc_discrete_distribution();
			SetBasicData(ret, name, config);
			return ret;
		}
		if (lcType == cc_uniform_dist_type) {
			cc_uniform_distribution* ret = new cc_uniform_distribution();
			SetBasicData(ret, name, config);
			return ret;
		}
		if (lcType == cc_rng_type) {
			cc_mt19937* ret = new cc_mt19937();
			SetBasicData(ret, name, config);
			return ret;
		}

		cc::Log(type, " 'type' does not have a creation declaration in cc_core_factory::CreateComponent().");
		return nullptr;
	}
}
