#ifndef UISCENE_H
#define UISCENE_H

#include "uibase.h"

#include <memory>
#include <vector>

class UIScene
{
public:
    UIScene();

    void addComponent(const UIBase &component) {
        _base.push_back(component);
    }

private:
    std::vector<UIBase> _base;

};

#endif // UISCENE_H
