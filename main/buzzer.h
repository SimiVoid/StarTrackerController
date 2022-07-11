#ifndef __BUZZER_H__
#define __BUZZER_H__

#define BUZZER_PIN

enum BuzzerMelody {
    BUZZER_MELODY_STARTUP = 0,
    BUZZER_MELODY_ENABLE_MOTOR,
    BUZZER_MELODY_DISABLE_MOTOR,
    BUZZER_MELODY_LOW_BATTERY,
    BUZZER_MELODY_BT_CONNECTED,
    BUZZER_MELODY_NONE
};

void vTaskBuzzer(void* pvParameters);

#endif // __BUZZER_H__