#ifndef __PROGRAM_GRAPH_HPP__
#define __PROGRAM_GRAPH_HPP__

#include <memory>
#include <vector>

#include "drone.h"
#include "Angel.h"

extern std::stack<mat4> mvStack;
extern mat4 modelView;

namespace cs4250{
struct DrawableGraph {
    std::unique_ptr<DrawableNode> root;
    void traverse(std::unique_ptr<DrawableNode>);
};

struct DrawableNode {   
    std::unique_ptr<Drawable> model;
    std::unique_ptr<DrawableNode> sibling;
    std::unique_ptr<DrawableNode> child;
};

struct Drawable {
    mat4 transformation;
    virtual void draw() = 0;
    std::vector<vec4> points;
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