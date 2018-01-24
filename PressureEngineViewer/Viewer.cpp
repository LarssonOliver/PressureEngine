#include "PressureEngine.h"

namespace PressureEngineViewer {

	using namespace Pressure;

	class EngineViewer {

	private: 
		PressureEngine engine;

		Entity* entity;
		Entity* entity2;
		std::vector<Light> lights;
		ParticleSystem* particleSystem;
		Water* water;

	public:
		EngineViewer() {
			engine.init();
			init();
			loop();
		}

		void init() {
			RawModel model = engine.loadObjModel("ball");
			ModelTexture* texture = new ModelTexture(engine.loadTexture("default.png"));
			texture->setShineDamper(10);
			texture->setReflectivity(1);
			TexturedModel texturedModel(model, texture);
			entity = new Entity(texturedModel, Vector3f(-4, 6, 5), Vector3f(0, 0, 0), 1.f);
			entity->setRotationSpeed(0, 0.5f, 0);
			entity2 = new Entity(texturedModel, Vector3f(-5, 0, 0), Vector3f(0), 5.f);
			lights.emplace_back(Vector3f(150000, 170000, 200000), Vector3f(1));
			water = new Water(engine.generateWater(Vector3f(-16, 0, -16)));
		}

		void loop() {
			long lastTime = Math::getTimeNano();
			double ns = 1000000000. / PRESSURE_TICKRATE;
			double delta = 0;
			long timer = Math::getTimeMillis();
			int frames = 0;
			long now;

			while (!engine.getWindow().isClosing()) {
				now = Math::getTimeNano();
				delta += (now - lastTime) / ns;
				lastTime = now;

				while (delta >= 1) {
					tick();
					delta--;
				}

				if (!engine.getWindow().isClosing())
					render();
				frames++;

#if PRESSURE_DEBUG
				if (Math::getTimeMillis() - timer > 1000) {
					timer += 1000;
					std::cout << "FPS: " << frames << std::endl;
					frames = 0;
				}
#endif
			}
		}

		void tick() {
			engine.tick();
			entity->tick();

			if (Keyboard::isPressed(GLFW_KEY_ESCAPE))
				engine.getWindow().close();
		}

		void render() {
			engine.process(*entity);
			engine.process(*entity2);
			engine.process(*water);
			engine.process(lights);
			engine.render();
		}

		void terminate() {
			engine.terminate();
		}

	};

}

int main() {

	PressureEngineViewer::EngineViewer e;

	return 0;

}