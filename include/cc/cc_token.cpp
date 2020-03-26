#include "cc/cc_token.h"

namespace cc
{
	int find_first_of(const std::vector<cc_token*>& tokenVec, CoreToken t) {

		for (size_t i = 0; i < tokenVec.size(); i++) {
			if (tokenVec[i]->type == t) {
				return (int)i;
			}
		}
		return -1;
	}

	std::vector<size_t> find_all_of(const std::vector<cc_token*>& tokenVec, CoreToken t) {

		std::vector<size_t> ret;
		for (size_t i = 0; i < tokenVec.size(); i++) {
			if (tokenVec[i]->type == t) {
				ret.push_back(i);
			}
		}
		return ret;
	}

}

