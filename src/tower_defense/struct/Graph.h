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
} // namespace tower_defense::ds
