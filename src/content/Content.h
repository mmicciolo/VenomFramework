#ifndef __CONTENT_H_
#define __CONTENT_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace VF {
	namespace Content {
		class Content {
		public:
			template<typename T, typename M> static T  * Load(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice) {
				M * contentLoader = new M();
				return contentLoader->Load<T>(fileName, graphicsDevice);
				//return nullptr;
				//return contentLoader->Load<T>(fileName);
				//Load2();
			}

			static void Load2() {
				Assimp::Importer importer;
				const aiScene * scene = importer.ReadFile("spider.obj", aiProcessPreset_TargetRealtime_Fast);
			}
		protected:
		private:
		};
	}
}

#endif