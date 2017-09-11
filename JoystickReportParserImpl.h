#include <usbhid.h>

#define RPT_GEMEPAD_LEN	5

struct GamePadEventData
{
		uint8_t X, Y, Z1, Z2, Rz;
};

enum DPADEnum
{
	DPAD_UP = 0x0,
	DPAD_UP_RIGHT = 0x1,
	DPAD_RIGHT = 0x2,
	DPAD_RIGHT_DOWN = 0x3,
	DPAD_DOWN = 0x4,
	DPAD_DOWN_LEFT = 0x5,
	DPAD_LEFT = 0x6,
	DPAD_LEFT_UP = 0x7
};

enum ButtonsEnum
{
	BUTTON_1 = 0x1,
	BUTTON_2 = 0x2,
	BUTTON_3 = 0x3,
	BUTTON_4 = 0x4,
	BUTTON_5 = 0x5,
	BUTTON_6 = 0x6,
	BUTTON_7 = 0x7,
	BUTTON_8 = 0x8,
	BUTTON_9 = 0x9,
	BUTTON_10 = 0x10
};

class JoystickEvents
{
	public:
		JoystickEvents();
		virtual ~JoystickEvents();

		virtual void OnGamePadChanged(const GamePadEventData *evt);
		virtual void OnHatSwitch(uint8_t hat);
		virtual void OnButtonUp(uint8_t but_id);
		virtual void OnButtonDn(uint8_t but_id);
};

class JoystickReportParserImpl: public HIDReportParser
{
		JoystickEvents *joyEvents;

		uint8_t oldPad[RPT_GEMEPAD_LEN];
		uint8_t oldHat;
		uint16_t oldButtons;

	public:
		JoystickReportParserImpl(JoystickEvents *evt);
		virtual ~JoystickReportParserImpl();

		virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};
