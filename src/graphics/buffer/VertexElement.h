#ifndef __VERTEX_ELEMENT_H_
#define __VERTEX_ELEMENT_H_

#include "../../math/Math.h"

namespace VF {
	namespace Graphics {

		enum VertexElementType {
			POSITION,
			COLOR,
			NORMAL,
			TEXTURECOORD,
			BONE_INDEX,
			BONE_WEIGHT
		};

		class VertexElement {
		public:
			VertexElementType vertexElementType;
			virtual unsigned int GetSize() { return 0; };
			virtual void * GetData() = 0;
		protected:
		private:
		};

		class PositionVertexElement : public VertexElement {
		public:
			PositionVertexElement(VF::Math::Vector3 position) { this->position = position; vertexElementType = POSITION; }
			unsigned int GetSize() { return 12; }
			void * GetData() { return &position; }
		protected:
		private:
			VF::Math::Vector3 position;
		};

		class ColorVertexElement : public VertexElement {
		public:
			ColorVertexElement(VF::Math::Vector4 color) { this->color = color; vertexElementType = COLOR; }
			unsigned int GetSize() { return 16; }
			void * GetData() { return &color; }
		protected:
		private:
			VF::Math::Vector4 color;
		};

		class NormalVertexElement : public VertexElement {
		public:
			NormalVertexElement(VF::Math::Vector3 normal) { this->normal = normal; vertexElementType = NORMAL; }
			unsigned int GetSize() { return 12; }
			void * GetData() { return &normal; }
		protected:
		private:
			VF::Math::Vector3 normal;
		};

		class TextureVertexElement : public VertexElement {
		public:
			TextureVertexElement(VF::Math::Vector2 texcoord) { this->texcoord = texcoord; vertexElementType = TEXTURECOORD; }
			unsigned int GetSize() { return 8; }
			void * GetData() { return &texcoord; }
		protected:
		private:
			VF::Math::Vector2 texcoord;
		};

		class BoneIndexVertexElement : public VertexElement {
		public:
			BoneIndexVertexElement(VF::Math::Vector4 boneIndex) { this->boneIndex = boneIndex; vertexElementType = BONE_INDEX; }
			unsigned int GetSize() { return 16; }
			void * GetData() { return &boneIndex; }
		protected:
		private:
			VF::Math::Vector4 boneIndex;
		};

		class BoneWeightVertexElement : public VertexElement {
		public:
			BoneWeightVertexElement(VF::Math::Vector4 boneWeight) { this->boneWeight = boneWeight; vertexElementType = BONE_WEIGHT; }
			unsigned int GetSize() { return 16; }
			void * GetData() { return &boneWeight; }
		protected:
		private:
			VF::Math::Vector4 boneWeight;
		};
	}
}

#endif