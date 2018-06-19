#ifndef __CONTENT_LOADER_H_
#define __CONTENT_LOADER_H_

#include <string>

namespace VF {
	namespace Content {
		class ContentLoader {
		public:
			ContentLoader() { }
			ContentLoader(std::string fileName) { this->fileName = fileName; }
			template<typename T> T  * Load(std::string fileName) { return nullptr; };
		protected:
			std::string fileName;
		private:
		};
	}
}

#endif