#include "Angel.h"
#include <memory>
#include "drone.h"

extern std::stack<mat4> mvStack;
extern mat4 modelView;

namespace cs4250{
struct DrawableGraph {
    std::unique_ptr<DrawableNode> root;
    void traverse(std::unique_ptr<DrawableNode>);
};

struct DrawableNode {
    mat4 transformation;
    virtual void draw(void) = 0;
    std::unique_ptr<DrawableNode> sibling;
    std::unique_ptr<DrawableNode> child;
};

inline void DrawableGraph::traverse(std::unique_ptr<DrawableNode>) {
    if (root == NULL) {
        return;
    }
    mvStack.push(modelView);
    modelView = modelView * (root->transformation);
    root->draw();
    traverse(root->child);
    modelView = mvStack.top();
    mvStack.pop();
    traverse(root->sibling);
}

}