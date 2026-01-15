#ifndef VIGEM_CLIENT_H
#define VIGEM_CLIENT_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VIGEM_SUCCESS(err) ((err) == VIGEM_ERROR_NONE)

typedef struct _VIGEM_CLIENT_T* PVIGEM_CLIENT;
typedef struct _VIGEM_TARGET_T* PVIGEM_TARGET;

typedef enum _VIGEM_ERROR {
    VIGEM_ERROR_NONE = 0x20000000,
    VIGEM_ERROR_BUS_NOT_FOUND = 0xE0000001,
    VIGEM_ERROR_NO_FREE_SLOT = 0xE0000002,
    VIGEM_ERROR_INVALID_TARGET = 0xE0000003,
    VIGEM_ERROR_REMOVAL_FAILED = 0xE0000004,
    VIGEM_ERROR_ALREADY_CONNECTED = 0xE0000005,
    VIGEM_ERROR_TARGET_NOT_INITIALIZED = 0xE0000006,
    VIGEM_ERROR_TARGET_NOT_CONNECTED = 0xE0000007,
    VIGEM_ERROR_BUS_ACCESS_FAILED = 0xE0000008,
    VIGEM_ERROR_INTERNAL_ERROR = 0xE0000009,
    VIGEM_ERROR_INVALID_BUFFER = 0xE000000A,
    VIGEM_ERROR_DEVICE_INDEX_OUT_OF_BOUNDS = 0xE000000B
} VIGEM_ERROR;

PVIGEM_CLIENT vigem_alloc();
void vigem_free(PVIGEM_CLIENT vigem);
VIGEM_ERROR vigem_connect(PVIGEM_CLIENT vigem);
void vigem_disconnect(PVIGEM_CLIENT vigem);

PVIGEM_TARGET vigem_target_x360_alloc();
PVIGEM_TARGET vigem_target_ds4_alloc();
void vigem_target_free(PVIGEM_TARGET target);

VIGEM_ERROR vigem_target_add(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);
VIGEM_ERROR vigem_target_remove(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);

typedef enum _XUSB_BUTTON {
    XUSB_GAMEPAD_DPAD_UP = 0x0001,
    XUSB_GAMEPAD_DPAD_DOWN = 0x0002,
    XUSB_GAMEPAD_DPAD_LEFT = 0x0004,
    XUSB_GAMEPAD_DPAD_RIGHT = 0x0008,
    XUSB_GAMEPAD_START = 0x0010,
    XUSB_GAMEPAD_BACK = 0x0020,
    XUSB_GAMEPAD_LEFT_THUMB = 0x0040,
    XUSB_GAMEPAD_RIGHT_THUMB = 0x0080,
    XUSB_GAMEPAD_LEFT_SHOULDER = 0x0100,
    XUSB_GAMEPAD_RIGHT_SHOULDER = 0x0200,
    XUSB_GAMEPAD_GUIDE = 0x0400,
    XUSB_GAMEPAD_A = 0x1000,
    XUSB_GAMEPAD_B = 0x2000,
    XUSB_GAMEPAD_X = 0x4000,
    XUSB_GAMEPAD_Y = 0x8000
} XUSB_BUTTON;

typedef struct _XUSB_REPORT {
    USHORT wButtons;
    BYTE bLeftTrigger;
    BYTE bRightTrigger;
    SHORT sThumbLX;
    SHORT sThumbLY;
    SHORT sThumbRX;
    SHORT sThumbRY;
} XUSB_REPORT, *PXUSB_REPORT;

#define XUSB_REPORT_INIT(r) { \
    ZeroMemory((r), sizeof(XUSB_REPORT)); \
}

VIGEM_ERROR vigem_target_x360_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, XUSB_REPORT report);

typedef struct _DS4_REPORT {
    BYTE bThumbLX;
    BYTE bThumbLY;
    BYTE bThumbRX;
    BYTE bThumbRY;
    BYTE bButtons1;
    BYTE bButtons2;
    BYTE bButtons3;
    BYTE bButtons4;
    BYTE bSpecial;
    BYTE bTriggerL;
    BYTE bTriggerR;
} DS4_REPORT, *PDS4_REPORT;

VIGEM_ERROR vigem_target_ds4_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, DS4_REPORT report);

#ifdef __cplusplus
}
#endif

#endif
