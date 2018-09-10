#pragma once


#include <functional>
#include <set>

namespace dev
{

/**
 * Detector for cycles in directed graphs. It returns the first
 * vertex on the path towards a cycle or a nullptr if there is
 * no reachable cycle starting from a given vertex.
 * 探测有向图中的回环。返回指向回环的首个点，如果从给定的顶点出发，没有回环，则返回nullptr
 */
template <typename V>
class CycleDetector
{
public:
	/// Initializes the cycle detector
	/// @param _visit function that is given the current vertex
	///               and is supposed to call @a run on all
	///               adjacent（邻近的） vertices.
	explicit CycleDetector(std::function<void(V const&, CycleDetector&)> _visit):
		m_visit(std::move(_visit))	
	{  }

	/// Recursively perform cycle detection starting
	/// (or continuing) with @param _vertex
	/// @returns the first vertex on the path towards a cycle from @a _vertex
	/// or nullptr if no cycle is reachable from @a _vertex.
	V const* run(V const& _vertex)
	{
		if (m_firstCycleVertex)
			return m_firstCycleVertex;
		// 统计_vertex在已经处理顶点中的出现次数，如果_vertxt已经出现过，表示出现回环
		if (m_processed.count(&_vertex))
			return nullptr;
		// 
		else if (m_processing.count(&_vertex))
			return m_firstCycleVertex = &_vertex;
		m_processing.insert(&_vertex);

		m_depth++;
		m_visit(_vertex, *this);
		m_depth--;
		if (m_firstCycleVertex && m_depth == 1)
			m_firstCycleVertex = &_vertex;

		m_processing.erase(&_vertex);
		m_processed.insert(&_vertex);
		return m_firstCycleVertex;
	}

private:
	std::function<void(V const&, CycleDetector&)> m_visit;
	std::set<V const*> m_processing;
	std::set<V const*> m_processed;
	size_t m_depth = 0;
	V const* m_firstCycleVertex = nullptr;
};

}
