#include <app/Scene.hpp>

namespace rack::app
{

struct Scene::Internal {};

Scene::Scene() = default;

Scene::~Scene() = default;

math::Vec Scene::getMousePos() {
	return {};
}

void Scene::step() {
}
void Scene::draw(const DrawArgs &args) {
}
void Scene::onHover(const HoverEvent &e) {
}
void Scene::onDragHover(const DragHoverEvent &e) {
}
void Scene::onHoverKey(const HoverKeyEvent &e) {
}
void Scene::onPathDrop(const PathDropEvent &e) {
}

} // namespace rack::app
