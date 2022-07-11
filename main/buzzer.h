#ifndef __BUZZER_H__
#define __BUZZER_H__

#define BUZZER_PIN

enum buzzer_melody {
    BUZZER_MELODY_STARTUP = 0,
    BUZZER_MELODY_ENABLE_MOTOR,
    BUZZER_MELODY_DISABLE_MOTOR,
    BUZZER_MELODY_LOW_BATTERY,
    BUZZER_MELODY_BT_CONNECTED
};

void control_buzzer_task(void* pvParameters);

#endif // __BUZZER_H__