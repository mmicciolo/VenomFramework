#ifndef __CAMERA_
#define __CAMERA_

#include "../math/Math.h"
#include "../input/keyboard/KeyboardState.h"
#include "../input/mouse/MouseState.h"

namespace VF {
	namespace Camera {
		struct PerspectiveProjectionParameters {
			float fieldOfView;
			int width;
			int height;
			float nearClip;
			float farClip;
		};
		class Camera {
		public:
			Camera(PerspectiveProjectionParameters parameters, VF::Math::Vector3 position, VF::Math::Vector3 rotation);
			void SetPerspectiveProjectionParameters(PerspectiveProjectionParameters parameters);
			void SetPosition(VF::Math::Vector3 position);
			void SetRotation(VF::Math::Vector3 rotation);
			VF::Math::Vector3 GetPosition();
			VF::Math::Vector3 GetRotation();
			VF::Math::Matrix4 GetProjectionMatrix();
			VF::Math::Matrix4 GetViewMatrix();
			void Update();
		protected:
			PerspectiveProjectionParameters parameters;
			VF::Math::Vector3 position = VF::Math::Vector3(0, 0, 0);
			VF::Math::Vector3 rotation = VF::Math::Vector3(0, 0, 0);
			VF::Math::Vector3 cameraUp = VF::Math::Vector3(0, 1, 0);
			VF::Math::Vector3 cameraDirection = VF::Math::Vector3(0, 0, 1);
			VF::Math::Matrix4 projectionMatrix;
			VF::Math::Matrix4 viewMatrix;
		private:
			void SetupPerspectiveProjection();
			void SetupView();
		};
	}
}

#endif