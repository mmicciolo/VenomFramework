#ifndef __KEY_STATE_
#define __KEY_STATE_

namespace KeyState {
	enum State {
		/// <summary>
		/// Key is released.
		/// </summary>
		Up,

		/// <summary>
		/// Key is pressed.
		/// </summary>
		Down,
	};
};


#endif