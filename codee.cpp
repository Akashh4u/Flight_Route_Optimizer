#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

// Flight Graph using Adjacency List
class FlightGraph {
private:
    unordered_map<string, vector<pair<string, int>>> adj; // Airport -> (Destination, Distance)

public:
    // Add a flight route
    void addRoute(const string &source, const string &destination, int distance) {
        adj[source].push_back({destination, distance});
        adj[destination].push_back({source, distance}); // Assuming bi-directional flights
    }

    // Dijkstra's Algorithm to find shortest flight route
    vector<string> findShortestRoute(const string &start, const string &end) {
        unordered_map<string, int> distance;
        unordered_map<string, string> previous;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

        // Initialize distances to infinity
        for (const auto &node : adj) {
            distance[node.first] = numeric_limits<int>::max();
        }
        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            int currDist = pq.top().first;
            pq.pop();

            if (current == end) break; // Stop when reaching the destination

            for (auto &neighbor : adj[current]) {
                string next = neighbor.first;
                int weight = neighbor.second;

                if (currDist + weight < distance[next]) {
                    distance[next] = currDist + weight;
                    previous[next] = current;
                    pq.push({distance[next], next});
                }
            }
        }

        // Construct the shortest route path
        vector<string> route;
        for (string at = end; at != ""; at = previous[at]) {
            route.push_back(at);
        }
        reverse(route.begin(), route.end());

        if (route.size() == 1) return {}; // No valid route found
        return route;
    }
};

int main() {
    FlightGraph graph;

    // Add flight routes
    graph.addRoute("JFK", "LAX", 3983);
    graph.addRoute("JFK", "ORD", 1181);
    graph.addRoute("ORD", "LAX", 2805);
    graph.addRoute("LAX", "DFW", 1989);
    graph.addRoute("DFW", "JFK", 2230);
    graph.addRoute("ORD", "ATL", 977);
    graph.addRoute("ATL", "MIA", 964);
    graph.addRoute("MIA", "LAX", 3753);
    graph.addRoute("ATL", "JFK", 1225);

    // Get user input
    string source, destination;
    cout << "Enter Source Airport Code: ";
    cin >> source;
    cout << "Enter Destination Airport Code: ";
    cin >> destination;

    // Find and print the optimized flight route
    vector<string> route = graph.findShortestRoute(source, destination);

    if (!route.empty()) {
        cout << "\nOptimized Flight Route: ";
        for (const auto &airport : route) {
            cout << airport << " -> ";
        }
        cout << "END\n";
    } else {
        cout << "\nNo available flight route between " << source << " and " << destination << ".\n";
    }

    return 0;
}
