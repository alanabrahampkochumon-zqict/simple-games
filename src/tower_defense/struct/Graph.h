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
#include <ranges>
#include <math/SimpleMath.h>

#include "Graph.h"

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


    ///+=+=+=+=+=+=+=+=+=+=
    ///    Greedy BFS
    ///+=+=+=+=+=+=+=+=+=+=


    // Single weighted edge
    // [from] --edge-- [to]
    struct WeightedEdge
    {
        // Node this edge originates from
        struct WeightedGraphNode* from;
        // Node this edge connects to
        struct WeightedGraphNode* to;
        // Weight of this edge
        float weight;
    };


    //           -w1-[node2]
    //          |
    // [node]-----w2-[node3]
    //          |
    //           -w3-[node4]
    struct WeightedGraphNode
    {
        // Data
        math::Vec2 position;
        // Outgoing edges
        std::vector<WeightedEdge*> edges;
    };

    struct WeightedGraph
    {
        std::vector<WeightedGraphNode*> nodes;
    };


    /// Structure for holding scratch data of GBFS
    struct GBFSScratch
    {
        const WeightedEdge* parentEdge = nullptr; /// The incoming edge
        float heuristic = 0.0f; /// The heuristic or approximate success
        bool inOpenSet = false; /// Node is yet to be traversed
        bool inClosedSet = false; /// Node has already been traversed
    };

    /// Structure for associating each node to its scratch struct
    using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;


    inline float computeHeuristic(const WeightedGraphNode* start, const WeightedGraphNode* goal) noexcept
    {
        // Manhattan distance (L2 Norm)
        return start->position.dist(goal->position);
    }

    /// Perform a greedy breadth first search on the given weighted graph
    /// and return a `bool` indicating whether a path between @p start and @p goal exists.
    inline bool gbfs(const WeightedGraph& graph, const WeightedGraphNode* start, const WeightedGraphNode* goal,
                     GBFSMap& outMap) noexcept
    {
        std::vector<const WeightedGraphNode*> openSet;

        // Start from "start" node and mark it as in closed set.
        const WeightedGraphNode* current = start;
        outMap[current].inClosedSet = true;

        do
        {
            // Compute the heuristic for each adjacent/neighboring node and add them to the open set
            // only if they aren't already in the closed set.
            for (const auto edge : current->edges)
            {
                GBFSScratch& data = outMap[edge->to];

                if (!data.inClosedSet)
                {
                    data.parentEdge = edge;
                    if (!data.inClosedSet)
                    {
                        data.heuristic = computeHeuristic(edge->to, goal);
                        data.inOpenSet = true;
                        openSet.emplace_back(edge->to);
                    }
                }
            }

            // Break from the loop is the open set is  empty
            if (openSet.empty())
                break;

            // Find the node in the open set with the lowest heuristic
            // and move it to the closed set and make it the current node
            auto iterator = std::ranges::min_element(
                openSet.begin(),
                openSet.end(),
                [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
                {
                    return outMap[a].heuristic < outMap[b].heuristic;
                }
            );

            current = *iterator;
            openSet.erase(iterator);
            outMap[current].inOpenSet = false;
            outMap[current].inClosedSet = true;
        }
        while (current != goal);
        return current == goal;
    }


    ///+=+=+=+=+=+=+=+=
    ///  A* Search
    ///+=+=+=+=+=+=+=+=

    /// Scratch structure used for A* search
    struct AStarScratch
    {
        const WeightedEdge* parentEdge = nullptr;
        bool inClosedSet = false;
        bool inOpenSet = false;
        float heuristic = 0.0f;
        float actualFromStart = 0.0f; /// Cost from start to the current node
    };

    using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

    /// Perform an a-star search and returns whether a path exist from @p start to @p goal.
    inline bool aStar(const WeightedGraph& graph, const WeightedGraphNode* start, const WeightedGraphNode* goal,
                      AStarMap& outMap)
    {
        // Create an open set for keeping track of traversed element
        std::vector<const WeightedGraphNode*> openSet;

        // Make the start the current node and mark it as closed in outMap
        const WeightedGraphNode* current = start;
        outMap[current].inClosedSet = true;

        // Compute the heuristic of the neighboring nodes and add them to the open set
        // if they're not in the closed set(already traversed set) already
        do
        {
            for (const WeightedEdge* edge : current->edges)
            {
                const WeightedGraphNode* neighbor = edge->to;
                AStarScratch& data = outMap[neighbor];

                if (!data.inClosedSet)
                {
                    // If the node is not the in open set then it must be the current node
                    if (!data.inOpenSet)
                    {
                        data.parentEdge = edge;
                        data.heuristic = computeHeuristic(neighbor, goal);
                        // Compute the actual cost
                        data.actualFromStart = outMap[current].actualFromStart + edge->weight;
                        data.inOpenSet = true;
                        openSet.emplace_back(neighbor);
                    }
                    else
                    {
                        // Compute the actual cost if this becomes the parent
                        float newG = outMap[current].actualFromStart + edge->weight;
                        if (newG < data.actualFromStart)
                        {
                            data.parentEdge = edge;
                            data.actualFromStart = newG;
                        }
                    }
                }

                // Break the loop if the open set is empty
                if (openSet.empty())
                    break;

                // Else make the node with the lowest heuristic + path cost the current node
                const auto minNodeIterator = std::ranges::min_element(openSet.begin(), openSet.end(),
                                                                      [&outMap](const WeightedGraphNode* a,
                                                                      const WeightedGraphNode* b)
                                                                      {
                                                                          return outMap[a].heuristic + outMap[a].
                                                                              actualFromStart < outMap[b].heuristic +
                                                                              outMap[b].actualFromStart;
                                                                      });

                // Make the min node the current
                current = *minNodeIterator;
                // Delete it from open set
                openSet.erase(minNodeIterator);
                // Mark it as closed
                outMap[current].inOpenSet = false;
                outMap[current].inClosedSet = true;
            }
        }
        while (current != goal);

        return false;
    }
} // namespace tower_defense::ds
