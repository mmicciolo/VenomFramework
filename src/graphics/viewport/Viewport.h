#ifndef __VIEWPORT_
#define __VIEWPORT_

namespace VF {
	namespace Graphics {
		class Viewport {
		public:
			Viewport(int x, int y, int width, int height);
			Viewport(int x, int y, int width, int height, float minDepth, float maxDepth);
			int GetX();
			int GetY();
			int GetWidth();
			int GetHeight();
			float GetMinDepth();
			float GetMaxDepth();
		protected:
		private:
			int x;
			int y;
			int width;
			int height;
			float minDepth;
			float maxDepth;
		};
	}
}

#endif