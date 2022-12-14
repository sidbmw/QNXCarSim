
#include <stdint.h>
#include <errno.h>
#include <sys/iomsg.h>

#define ENGINE_TOGGLE (_IO_MAX+200)
#define THROTTLE_TOGGLE (_IO_MAX+201)
#define BRAKES_TOGGLE (_IO_MAX+202)
#define INDICATOR_TOGGLE (_IO_MAX+203)
#define AIRBAG_TOGGLE (_IO_MAX+204)
#define STEERING_TOGGLE (_IO_MAX+205)

#define SERVER_NAME "start_car"

// Engine toggle message
typedef struct engine_toggle_msg_t {
    uint16_t type;
} engine_toggle_msg_t;

// Throttle toggle message
typedef struct throttle_toggle_msg_t {
    uint16_t type;
    int pressure;
} throttle_toggle_msg_t;

// Brake toggle message
typedef struct brakes_toggle_msg_t {
    uint16_t type;
    int pressure;
} brakes_toggle_msg_t;

// Indicator toggle message
typedef struct indicator_toggle_msg_t {
    uint16_t type;
    //left = 0, right = 1
    unsigned char left_right;
} indicator_toggle_msg_t;

// Airbag toggle message
typedef struct airbag_toggle_msg_t {
    uint16_t type;
} airbag_toggle_msg_t;

// Steering
typedef struct steering_toggle_msg_t {
    uint16_t type;
    //angle: 90 degrees - straight
    //angles: 0 to 89 degrees - left
    //angles: 91 - 180 - right
    unsigned short int angle;
} steering_toggle_msg_t;
