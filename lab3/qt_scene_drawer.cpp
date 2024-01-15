#include "qt_scene_drawer.h"
#include "QPainter"

Qt_scene_drawer::Qt_scene_drawer(QPicture pixmap) {
    _pixmap = pixmap;
}


void Qt_scene_drawer::draw_scene(std::shared_ptr<Scene> scene) {
    QPainter painter(&_pixmap);
    painter.translate(_pixmap.width() / 2, _pixmap.height() / 2);
    painter.fillRect(-_pixmap.width(), -_pixmap.height(), _pixmap.width() * 2, _pixmap.height() * 2, QBrush(QColor(Qt::GlobalColor::white)));
    painter.setPen(QColor(Qt::GlobalColor::black));
    std::vector<Figure> fig = scene->get_figures();
    for (size_t i = 0; i < fig[0].get_edges()->size(); i++) {
        painter.drawLine(fig[0].get_edges()->at(i).get_begin().get_position().X, fig[0].get_edges()->at(i).get_begin().get_position().Y,
                fig[0].get_edges()->at(i).get_end().get_position().X, fig[0].get_edges()->at(i).get_end().get_position().Y);
    }
}
