#ifndef __FIRST_PERSON_CAMERA_
#define __FIRST_PERSON_CAMERA_

#include "Camera.h"
#include "../window/IWindow.h"

namespace VF {
	namespace Camera {
		class FirstPersonCamera : public Camera {
		public:
			FirstPersonCamera(PerspectiveProjectionParameters parameters, VF::Math::Vector3 position, VF::Math::Vector3 rotation);
			void Update();
			void Move(VF::Window::IWindow * window, VF::Input::KeyboardState keyboardState, VF::Input::MouseState mouseState);
		protected:
		private:
			bool firstMouse = true;
			float leftRightRotation = 0.0f;
			float upDownRotation = 0.0f;
		};
	}
}

#endif