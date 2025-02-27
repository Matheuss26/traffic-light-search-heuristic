#include "assert.h"
#include "traffic_graph.h"

using namespace traffic;
using namespace std;

TimeUnit testCycle = 20;
size_t numberOfTestVertices = 5;
Graph::Edge	edge1 = {0, 1},
			edge2 = {1, 2},
			edge3 = {2, 3},
			edge4 = {3, 0},
			edge5 = {0, 4},
			edge6 = {4, 2};
Weight	weight1 = 7,
		weight2 = 12,
		weight3 = 19,
		weight4 = 3,
		weight5 = 10,
		weight6 = 6;

class MockGraph : public Graph {
	private:
		mutable unordered_map<Vertex, unordered_map<Vertex, Weight>> adjacencyList;
	public:
		MockGraph (void) : Graph(numberOfTestVertices, testCycle) {
			this->adjacencyList[0][1] = weight1;
			this->adjacencyList[1][0] = weight1;

			this->adjacencyList[1][2] = weight2;
			this->adjacencyList[2][1] = weight2;

			this->adjacencyList[2][3] = weight3;
			this->adjacencyList[3][2] = weight3;

			this->adjacencyList[3][0] = weight4;
			this->adjacencyList[0][3] = weight4;

			this->adjacencyList[0][4] = weight5;
			this->adjacencyList[4][0] = weight5;

			this->adjacencyList[4][2] = weight6;
			this->adjacencyList[2][4] = weight6;
		}
		virtual Weight weight(const Edge& edge) const {
			if (edge == edge1) {
				return weight1;
			} else if (edge == edge2) {
				return weight2;
			} else if (edge == edge3) {
				return weight3;
			} else if (edge == edge4) {
				return weight4;
			} else if (edge == edge5) {
				return weight5;
			} else if (edge == edge6) {
				return weight6;
			} else {
				return -1;
			}
		}
		virtual const std::unordered_map<Vertex, Weight>& neighborsOf(Vertex vertex) const {
			return this->adjacencyList[vertex];
		}
};

int main (void) {
	Solution*	solution = NULL;
	MockGraph mockGraph;

	test_case("solution instantiation throws no errors") {
		solution = new Solution(numberOfTestVertices);
	} end_test_case;

	test_case("set timing") {
		solution->setTiming(1, 3);
		assert_equal(solution->getTiming(1), 3);
	} end_test_case;

	test_case("unspecified timings have value 0") {
		assert_equal(solution->getTiming(0), 0);
	} end_test_case;

	test_case("creating random initial solution throws no errors") {
		constructRandomSolution(mockGraph);
	} end_test_case;

	test_case("random solution has at least one timing that's not 0") {
		bool found = false;
		for (size_t i = 0; i < mockGraph.getNumberOfVertices() && !found; i++) {
			if (mockGraph.getTiming(i) != 0) {
				found = true;
			}
		}
		assert_true(found);
	} end_test_case;

	test_case("random solution has all timings in the interval [0, cycle)") {
		TimeUnit timing;
		for (size_t i = 0; i < mockGraph.getNumberOfVertices(); i++) {
			timing = mockGraph.getTiming(i);
			assert_true(timing >= 0 && timing < testCycle);
		}
	} end_test_case;

	test_case("creating heuristic initial solution throws no errors") {
		constructHeuristicSolution(mockGraph);
	} end_test_case;

	test_case("heuristic solution has at least one timing that's not 0") {
		bool found = false;
		for (size_t i = 0; i < mockGraph.getNumberOfVertices() && !found; i++) {
			if (mockGraph.getTiming(i) != 0) {
				found = true;
			}
		}
		assert_true(found);
	} end_test_case;

	test_case("heuristic solution has all timings in the interval [0, cycle)") {
		TimeUnit timing;
		for (size_t i = 0; i < mockGraph.getNumberOfVertices(); i++) {
			timing = mockGraph.getTiming(i);
			assert_true(timing >= 0 && timing < testCycle);
		}
	} end_test_case;

	test_case("destroying directly instatited solution throws no errors") {
		delete solution;
	} end_test_case;

}
