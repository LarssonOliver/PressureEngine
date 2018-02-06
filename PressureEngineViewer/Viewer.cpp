#include "PressureEngine.h"

namespace PressureEngineViewer {

	using namespace Pressure;

	class EngineViewer {

	private: 
		PressureEngine engine;

		std::vector<Entity> entities;
		std::vector<Light> lights;
		ParticleSystem* particleSystem;
		std::vector<Water> waters;

	public:
		EngineViewer() {
			engine.init();
			init();
			loop();
		}

		void init() {
			// Island
			RawModel islandModel = engine.loadObjModel("Island");
			ModelTexture islandTexture(engine.loadTexture("Island.png"));
			islandTexture.setFakeLighting(true);
			islandTexture.setShineDamper(10);
			islandTexture.setReflectivity(.1f);
			TexturedModel island(islandModel, islandTexture);
			entities.emplace_back(island, Vector3f(0), Vector3f(0, 0, 0), 8.f);

			RawModel jettyModel = engine.loadObjModel("Jetty");
			ModelTexture jettyTexture(engine.loadTexture("Jetty.png"));
			jettyTexture.setShineDamper(10);
			jettyTexture.setReflectivity(.5f);
			TexturedModel jetty(jettyModel, jettyTexture);
			entities.emplace_back(jetty, Vector3f(-12, 0.5f, 6), Vector3f(0, 155, 0), 2.f);

			RawModel grassModel = engine.loadObjModel("Grass");
			grassModel.setWindAffected(true);
			RawModel grass2Model = engine.loadObjModel("Grass2");
			grass2Model.setWindAffected(true);
			ModelTexture grassTexture(engine.loadTexture("Grass.png"));
			ModelTexture grass2Texture(engine.loadTexture("Grass.png"));
			TexturedModel grass(grassModel, grassTexture);
			TexturedModel grass2(grass2Model, grass2Texture);
			Random<float> r(-2, 2);
			entities.emplace_back(grass, Vector3f(r.next(), 1, r.next()), Vector3f(0, r.next() * 180, 0), 1.0);
			entities.emplace_back(grass, Vector3f(r.next(), 1, r.next()), Vector3f(0, r.next() * 180, 0), 1.0);
			entities.emplace_back(grass, Vector3f(r.next(), 1, r.next()), Vector3f(0, r.next() * 180, 0), 1.0);
			entities.emplace_back(grass2, Vector3f(r.next(), 1, r.next()), Vector3f(0, r.next() * 180, 0), 1.0);
			entities.emplace_back(grass2, Vector3f(r.next(), 1, r.next()), Vector3f(0, r.next() * 180, 0), 1.0);
			entities.emplace_back(grass2, Vector3f(r.next(), 1, r.next()), Vector3f(0, r.next() * 180, 0), 1.0);
			
			// Lights
			lights.emplace_back(Vector3f(150000, 170000, 200000), Vector3f(1));

			// Waters
			waters.emplace_back(engine.generateWater(Vector3f(-39, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-39, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-23, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-23, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-7, 0, -5)));
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
			for (auto& entity : entities) {
				entity.tick();
			}

			if (Keyboard::isPressed(GLFW_KEY_ESCAPE))
				engine.getWindow().close();
		}

		void render() {
			engine.process(entities);
			engine.process(waters);
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