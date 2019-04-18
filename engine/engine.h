#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

class Scene {
public:
  Scene() = default;
  virtual ~Scene();
  virtual void load() = 0;
  virtual void loadAsync();
  virtual void unLoad();
  virtual void update(const double& dt);
  virtual void render();
  bool isLoaded() const;
  std::shared_ptr<Entity> makeEntity();

  EntityManager ents;

protected:
  void setLoaded(bool);
private:
  mutable bool _loaded;
  mutable std::future<void> _loadedFuture;
  mutable std::mutex _loadedMtx;
};

class Engine {
public:
  Engine() = delete;
  static void start(unsigned int width, unsigned int height,
                    const std::string& gameName, Scene* scn);
  static void changeScene(Scene*);
  static Scene* getActiveScene() { return _activeScene; }
  static sf::RenderWindow& getWindow();
  static sf::Vector2u getWindowSize();
  static void setVsync(bool b);
  static void switchWindowMode();

private:
  static Scene* _activeScene;
  static std::string _gameName;
  static void update();
  static void render(sf::RenderWindow& window);
};

namespace timing {
// Return time since Epoc
long long now();
// Return time since last() was last called.
long long last();
} // namespace timing