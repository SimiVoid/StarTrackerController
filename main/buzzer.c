#include "buzzer.h"

void vTaskBuzzer(void* pvParameters) {
    enum buzzer_melody selected = (enum buzzer_melody)pvParameters;

    switch (selected) {
        case BUZZER_MELODY_STARTUP:
            // Play startup melody
            break;
        case BUZZER_MELODY_ENABLE_MOTOR:
            // Play enable motor melody
            break;
        case BUZZER_MELODY_DISABLE_MOTOR:
            // Play disable motor melody
            break;
        case BUZZER_MELODY_LOW_BATTERY:
            // Play low battery melody
            break;
        case BUZZER_MELODY_BT_CONNECTED:
            // Play bt connected melody
            break;
        case BUZZER_MELODY_NONE:
            // Play nothing
            break;
    }
}