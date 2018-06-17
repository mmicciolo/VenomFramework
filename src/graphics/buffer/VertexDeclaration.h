#ifndef __VERTEX_DECLARATION_H_
#define __VERTEX_DECLARATION_H_

namespace bgfx {
	struct VertexDecl;
}

namespace VF {
	namespace Graphics {
		class VertexDeclaration {
		public:
			virtual void CreateVertexDeclaration() = 0;
			virtual void * ToByteArray() = 0;
			virtual int GetVertexStride() = 0;
			bgfx::VertexDecl * getVertexDeclaration() { return vertexDeclaration;  }
		protected:
			bgfx::VertexDecl * vertexDeclaration;
		private:
		};
	}
}

#endif