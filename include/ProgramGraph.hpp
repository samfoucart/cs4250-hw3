#ifndef __PROGRAM_GRAPH_HPP__
#define __PROGRAM_GRAPH_HPP__

#include <memory>
#include <vector>

#include "SpaceProgram.hpp"
#include "Angel.h"
#include "Drawable.hpp"

namespace cs4250{
extern std::stack<mat4> mvStack;
extern mat4 modelView;


struct DrawableGraph {
    std::unique_ptr<DrawableNode> root;
    void traverse(std::unique_ptr<DrawableNode>);
};

struct DrawableNode {   
    std::unique_ptr<Drawable> model;
    std::unique_ptr<DrawableNode> sibling;
    std::unique_ptr<DrawableNode> child;
};   

inline void DrawableGraph::traverse(std::unique_ptr<DrawableNode>) {
    if (root == NULL) {
        return;
    }
    mvStack.push(modelView);
    modelView = modelView * (root->model->transformation);
    root->model->draw();
    traverse(root->child);
    modelView = mvStack.top();
    mvStack.pop();
    traverse(root->sibling);
}

}

#endif