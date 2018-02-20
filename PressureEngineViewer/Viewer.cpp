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
			entities.emplace_back(jetty, Vector3f(-10, 0.5f, 4), Vector3f(0, 185, 0), 2.f);

			RawModel treeModel = engine.loadObjModel("Tree");
			ModelTexture treeTexture = engine.loadTexture("Tree.png");
			TexturedModel tree(treeModel, treeTexture);
			entities.emplace_back(tree, Vector3f(-31.5, 0, -14), Vector3f(3, 0, 0), 8.0);

			RawModel tombstoneModel = engine.loadObjModel("Tombstone");
			ModelTexture tombstoneTexture(engine.loadTexture("Tombstone.png"));
			TexturedModel tombstone(tombstoneModel, tombstoneTexture);
			entities.emplace_back(tombstone, Vector3f(-27, .3, -13.7), Vector3f(0, 88, 0), 1.2);

			RawModel wellModel = engine.loadObjModel("Well");
			ModelTexture wellTexture(engine.loadTexture("Well.png"));
			TexturedModel well(wellModel, wellTexture);
			entities.emplace_back(well, Vector3f(4, 0.1, 18), Vector3f(0, 195, 0), 1.6);
			
			RawModel rackModel = engine.loadObjModel("Fishingrack");
			ModelTexture rackTexture = engine.loadTexture("Fishingrack.png");
			TexturedModel rack(rackModel, rackTexture);
			entities.emplace_back(rack, Vector3f(-3, 0.4, 16), Vector3f(0, 150, 0), 1);

			// Fences
			RawModel fenceModel = engine.loadObjModel("Fence");
			RawModel fence2Model = engine.loadObjModel("Fence2");
			ModelTexture fenceTexture = engine.loadTexture("Jetty.png");
			ModelTexture fence2Texture = engine.loadTexture("Jetty.png");
			TexturedModel fence(fenceModel, fenceTexture);
			TexturedModel fence2(fence2Model, fence2Texture);
			entities.emplace_back(fence, Vector3f(-7, 0.3, 19), Vector3f(0, 145, 0), 2.7);
			entities.emplace_back(fence2, Vector3f(-0.2, 0.1, 21.5), Vector3f(0, 173, 0), 2.7);
			entities.emplace_back(fence, Vector3f(7, -0.1, 22.5), Vector3f(0, 173, 0), 2.7);
			entities.emplace_back(fence, Vector3f(14, -0.4, 23), Vector3f(0, 175, 0), 2.7);
			entities.emplace_back(fence2, Vector3f(21, -0.6, 23), Vector3f(0, 183, 0), 2.7);

			// Stones			
			RawModel stoneModels[3] = { engine.loadObjModel("Stone"), engine.loadObjModel("Stone2"), engine.loadObjModel("Stone3") };
			ModelTexture stoneTextures[3] = { engine.loadTexture("Stone.png"), engine.loadTexture("Stone.png"), engine.loadTexture("Stone.png") };
			TexturedModel stones[3] = { { stoneModels[0], stoneTextures[0] }, { stoneModels[1], stoneTextures[1] }, { stoneModels[2], stoneTextures[2] } };

			entities.emplace_back(stones[0], Vector3f(-41.2, -1, .6), Vector3f(10, 50, 10), 2.8);
			entities.emplace_back(stones[1], Vector3f(-41, -1.4, 3.5), Vector3f(20), 3.3);
			entities.emplace_back(stones[2], Vector3f(-40.5, -.6, 5), Vector3f(-10), 1.6);
			entities.emplace_back(stones[2], Vector3f(-40.2, -2.2, 2), Vector3f(-10, 70, 0), 1.6);

			entities.emplace_back(stones[1], Vector3f(-30, -7.2, 1), Vector3f(-10, 70, 0), 1);
			entities.emplace_back(stones[0], Vector3f(-26, -5.9, 9), Vector3f(-10, 70, 0), .6);
			entities.emplace_back(stones[2], Vector3f(-21, -5.2, 13), Vector3f(-10, 70, 0), .6);

			entities.emplace_back(stones[0], Vector3f(-12, 0.3, -20), Vector3f(0, 0, 0), 2.3);

			if (std::stoi(Properties::Inst()->get("renderGrass")) == 1) { 				
				RawModel grassModel = engine.loadObjModel("Grass");
				grassModel.setWindAffected(true);
				RawModel grass2Model = engine.loadObjModel("Grass2");
				grass2Model.setWindAffected(true);
				ModelTexture grassTexture(engine.loadTexture("Grass.png"));
				ModelTexture grass2Texture(engine.loadTexture("Grass.png"));
				TexturedModel grass(grassModel, grassTexture);
				TexturedModel grass2(grass2Model, grass2Texture);
				setGrassPatch(-38, 1, -12, grass, grass2, -0.2, 0);
				setGrassPatch(-39.5, 1.2, -9, grass, grass2, -0.25, .05);
				setGrassPatch(-40, 1.1, -5, grass, grass2, -0.45, -.25);
				setGrassPatch(-39, 0.6, 12, grass, grass2, -0.17, .2);
				setGrassPatch(-39, 0.75, 15, grass, grass2, -0.17, .2);
				setGrassPatch(-38, 0.75, 18, grass, grass2, -0.05, 0.15);
				setGrassPatch(-35, 0.7, 20, grass, grass2, -0.10, 0.15);
				setGrassPatch(-31, 0.8, 22, grass, grass2, 0.10, 0.15);
				setGrassPatch(-28, 0.8, 22, grass, grass2, -0.15, 0.15);
				setGrassPatch(-25, 0.7, 22, grass, grass2, 0.10, 0.25);
				setGrassPatch(-22, 0.6, 22, grass, grass2, 0.10, 0.30);
				setGrassPatch(-19, 0.6, 22, grass, grass2, 0.10, 0.15);
				setGrassPatch(-16, 0.7, 22, grass, grass2, 0.20, 0.25);
				setGrassPatch(-13, .5, 20, grass, grass2, 0.20, 0.3);
				setGrassPatch(-8, 0.7, 22, grass, grass2, -0.20, 0.3);
			}

			// Lights
			lights.emplace_back(Vector3f(150000, 170000, 200000), Vector3f(1));

			// Waters
			waters.emplace_back(engine.generateWater(Vector3f(-41, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-41, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-25, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-25, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-9, 0, -5)));

			ParticleTexture particleTex = engine.loadParticleTexture("WaterParticles.png", 4, false);
			particleSystem = new ParticleSystem(particleTex, 128, (Vector3f&)Vector3f(-.09, 0, 0), 0.01, 1.4 * 60);
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
			particleSystem->generateParticles((Vector3f&)Vector3f(-41, 0, 3), Vector3f(.2, .1, 2));
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
			//engine.process(GuiTexture(4, Vector2f(0.5), Vector2f(0.5), false));
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
				for (int i = 0; i < 4; i++) {
					offsetX = r.next();
					offsetZ = r.next();
					offsetY = offsetX/2 * slopeX + offsetZ/2 * slopeZ;
					if (i < 2)
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