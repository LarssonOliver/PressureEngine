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

		Random<float> r;

	public:
		EngineViewer() : r(-2, 2) {
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

			RawModel treeModel = engine.loadObjModel("Tree");
			ModelTexture treeTexture(engine.loadTexture("Tree.png"));
			TexturedModel tree(treeModel, treeTexture);
			entities.emplace_back(tree, Vector3f(-30.5, 0, -14), Vector3f(), 8.0);

			if (std::stoi(Properties::Inst()->get("renderGrass")) == 1) { 				
				RawModel grassModel = engine.loadObjModel("Grass");
				grassModel.setWindAffected(true);
				RawModel grass2Model = engine.loadObjModel("Grass2");
				grass2Model.setWindAffected(true);
				ModelTexture grassTexture(engine.loadTexture("Grass.png"));
				ModelTexture grass2Texture(engine.loadTexture("Grass.png"));
				TexturedModel grass(grassModel, grassTexture);
				TexturedModel grass2(grass2Model, grass2Texture);
				setGrassPatch(-39, 0.75, 12, grass, grass2, -0.17, 0);
				setGrassPatch(-39, 0.75, 15, grass, grass2, -0.17, 0);
				setGrassPatch(-38, 0.55, 18, grass, grass2, -0.05, -0.05);
				setGrassPatch(-35, 0.5, 20, grass, grass2, 0.10, 0.05);
				setGrassPatch(-31, 0.8, 22, grass, grass2, 0.10, 0.05);
				setGrassPatch(-28, 0.8, 22, grass, grass2, -0.15, 0.15);
				setGrassPatch(-25, 0.7, 22, grass, grass2, 0.10, 0.25);
				setGrassPatch(-22, 0.7, 22, grass, grass2, 0.10, 0.25);
				setGrassPatch(-19, 0.7, 22, grass, grass2, 0.10, 0.1);
				setGrassPatch(-16, 0.9, 22, grass, grass2, 0.20, 0.2);
				setGrassPatch(-13, 1, 20, grass, grass2, 0.20, 0.3);
			}

			// Lights
			lights.emplace_back(Vector3f(150000, 170000, 200000), Vector3f(1));

			// Waters
			waters.emplace_back(engine.generateWater(Vector3f(-41, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-41, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-25, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-25, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-9, 0, -5)));
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

	private:
		void setGrassPatch(const float x, const float y, const float z, const TexturedModel& grass, const TexturedModel& grass2, const float slopeX = 0.f, const float slopeZ = 0.f) {			
			if (false) { // If i want to render grass as planes.
				RawModel model = engine.loadObjModel("Plane");
				ModelTexture def = engine.loadTexture("default.png");
				TexturedModel plane(model, def);
				entities.emplace_back(plane, Vector3f(x, y, z), Vector3f(180.0 / Math::PI * atan(-slopeZ / 2), 0, 180.0 / Math::PI * atan(slopeX / 2)), 2.0f);
			} else {
				float offsetX, offsetZ, offsetY;
				for (int i = 0; i < 16; i++) {
					offsetX = r.next();
					offsetZ = r.next();
					offsetY = offsetX/2 * slopeX + offsetZ/2 * slopeZ;
					if (i < 8)
						entities.emplace_back(grass, Vector3f(x + offsetX, y + offsetY, z + offsetZ), Vector3f(0, r.next() * 180, 0), 1.0 + 0.3 * r.next());
					else
						entities.emplace_back(grass2, Vector3f(x + offsetX, y + offsetY, z + offsetZ), Vector3f(0, r.next() * 180, 0), 1.0 + 0.3 * r.next());
				}
			}
		}

	};

}

int main() {

	PressureEngineViewer::EngineViewer e;

	return 0;

}