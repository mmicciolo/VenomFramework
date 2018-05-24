#ifndef __MOUSE_STATE_
#define __MOUSE_STATE_

#include "../ButtonState.h"
#include "MouseButtons.h"

namespace VF {
	namespace Input {

		class MousePosition {
		public:
			int x, y;
		protected:
		private:
		};

		struct MouseData {
			MousePosition position;
			int scrollWheelValue;
			ButtonState::State leftButton;
			ButtonState::State rightButton;
			ButtonState::State middleButton;
			ButtonState::State XButton1;
			ButtonState::State XButton2;
		};

		class MouseState {
		public:
			friend class Mouse;
			friend class IWindow;
			bool IsButtonPressed(MouseButtons::Buttons button);
			bool IsButtonReleased(MouseButtons::Buttons button);
			MousePosition GetMousePosition();
			int GetScrollWheelValue();
		protected:
		private:
			MouseData mouseData;
		};
	}
}

#endif