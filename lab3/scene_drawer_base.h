#ifndef SCENE_DRAWER_BASE_H
#define SCENE_DRAWER_BASE_H
#include "scene.h"
#include <QObject>
#include <QPixmap>
#include <QPicture>

class Scene_drawer_base {
public:
    virtual void draw_scene(std::shared_ptr<Scene> scene) = 0;
    virtual ~Scene_drawer_base() {}
};

#endif // SCENE_DRAWER_BASE_H
