#ifndef QT_SCENE_DRAWER_H
#define QT_SCENE_DRAWER_H
#include "scene_drawer_base.h"
#include "figure.h"

class Qt_scene_drawer : public Scene_drawer_base {
private:
    QPicture _pixmap;
public:
    Qt_scene_drawer(QPicture pixmap);
    void draw_scene(std::shared_ptr<Scene> scene) override;
};

#endif // QT_SCENE_DRAWER_H
