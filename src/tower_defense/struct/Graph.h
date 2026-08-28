#pragma once
/**
 * @file Graph.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 28, 2026
 *
 * @brief Graph data structure.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <queue>
#include <unordered_map>
#include <vector>

namespace tower_defense::ds
{
    struct GraphNode
    {
        std::vector<GraphNode*> adjacent;
    };

    struct Graph
    {
        std::vector<GraphNode*> nodes;
    };

    struct WeightedGraphNode
    {
        // Incoming edges
        std::vector<WeightedGraphNode*> fromNodes;
        // Outgoing edges
        std::vector<WeightedGraphNode*> toNodes;
        // Weight of this edge
        float weight;
    };

    struct WeightedGraph
    {
        // Outgoing edges
        std::vector<WeightedGraphNode*> nodes;
    };

    /// Keeps track parent child relationship to make route reconstruction easy
    using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

    /// Traverse a graph using BFS and returns whether a path exists between start and goal
    bool bfs(const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap) noexcept
    {
        bool hasPath = false;

        // Add the parent node to the queue
        std::queue<const GraphNode*> queue;
        queue.emplace(start);

        // Traverse the graph until the full nodes are traversed
        while (!queue.empty())
        {
            // FIFO: Pop the last element
            const GraphNode* current = queue.front();
            queue.pop();

            // If the current node and goals are the same, then we found a path.
            if (current == goal)
            {
                hasPath = true;
                break;
            }

            // Add the neighboring nodes
            for (const auto neighbor : current->adjacent)
            {

                // If the parent is nullptr, then it hasn't been enqueued yet
                // or it's the root node.
                const auto parent = outMap[neighbor];

                if (parent == nullptr && parent != start)
                {
                    // Add the neighboring node to the queue
                    outMap[neighbor] = current;
                    queue.emplace(neighbor);
                }
            }
        }

        return hasPath;
    }
} // namespace tower_defense::ds
