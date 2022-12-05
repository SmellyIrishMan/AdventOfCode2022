#include "pch.h"
#include "framework.h"
#include <utility>
#include <vector>
#include <algorithm>

namespace AdventOfCode
{
	using AssignedSections = std::pair<unsigned int, unsigned int>;
	using AssignedSectionsPair = std::pair<AssignedSections, AssignedSections>;
	using AssignedSectionsPairList = std::vector<AssignedSectionsPair>;

	auto IsPartiallyOverlapping = [](const AssignedSections& a, const AssignedSections& b) {
		return (a.first >= b.first && a.first <= b.second) || (a.second >= b.first && a.second <= b.second);
	};

	auto IsFullyOverlapedBy = [](const AssignedSections& a, const AssignedSections& b) {
		return a.first >= b.first && a.second <= b.second;
	};

	unsigned int Day4FindFullyOverlappingSections(AssignedSectionsPairList sectionPairList)
	{
		size_t numberOfFullyOverlappingSections = std::count_if(begin(sectionPairList), end(sectionPairList), [&](const AssignedSectionsPair& pair) {
			const auto& [assignedSectionsA, assignedSectionsB] = pair;
			return IsFullyOverlapedBy(assignedSectionsA, assignedSectionsB) || IsFullyOverlapedBy(assignedSectionsB, assignedSectionsA);
		});

		return static_cast<unsigned int>(numberOfFullyOverlappingSections);
	}

	unsigned int Day4FindFullOrPartiallyOverlappingSections(AssignedSectionsPairList sectionPairList)
	{
		size_t numberOfFullyOverlappingSections = std::count_if(begin(sectionPairList), end(sectionPairList), [&](const AssignedSectionsPair& pair) {
			const auto& [assignedSectionsA, assignedSectionsB] = pair;
			bool fullyOverlapping = IsFullyOverlapedBy(assignedSectionsA, assignedSectionsB) || IsFullyOverlapedBy(assignedSectionsB, assignedSectionsA);
			bool partiallyOverlapping = IsPartiallyOverlapping(assignedSectionsA, assignedSectionsB) || IsPartiallyOverlapping(assignedSectionsB, assignedSectionsA);
			return fullyOverlapping || partiallyOverlapping;
		});

		return static_cast<unsigned int>(numberOfFullyOverlappingSections);
	}
}