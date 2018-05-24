#ifndef __BUTTON_STATE_
#define __BUTTON_STATE_

namespace VF {
	namespace Input {
		namespace ButtonState {
			enum State {
				/// <summary>
				/// The button is released.
				/// </summary>
				Released,

				/// <summary>
				/// The button is pressed.
				/// </summary>
				Pressed
			};
		}
	}
}

#endif