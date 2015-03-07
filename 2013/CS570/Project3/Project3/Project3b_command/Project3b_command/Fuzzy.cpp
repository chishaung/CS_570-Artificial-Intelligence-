#include "Fuzzy.h"
#include <algorithm>


void fuzzy::fuzzy_set_X() {
    
    RIGHT_THURST = min(fuzzy_value_left_far, fuzzy_value_high_height);
    RIGHT_THURST = min(fuzzy_value_left_far, fuzzy_value_med_height);
    RIGHT_THURST = min(fuzzy_value_left_far, fuzzy_value_low_height);
    
    NO_THURST = min(fuzzy_value_med_far, fuzzy_value_high_height);
    NO_THURST = min(fuzzy_value_med_far, fuzzy_value_med_height);
    NO_THURST = min(fuzzy_value_med_far, fuzzy_value_low_height);
    
    LEFT_THURST = min(fuzzy_value_right_far, fuzzy_value_high_height);
    LEFT_THURST = min(fuzzy_value_right_far, fuzzy_value_med_height);
    LEFT_THURST = min(fuzzy_value_right_far, fuzzy_value_low_height);
    }

float fuzzy::defuzzy_X() {
    if (NO_THURST > LEFT_THURST && NO_THURST > RIGHT_THURST) {
        return 0.0;
    }
    
    else if ( RIGHT_THURST > NO_THURST && RIGHT_THURST > LEFT_THURST) {
        return -0.5;
    }
    
    else if (LEFT_THURST > NO_THURST && LEFT_THURST > RIGHT_THURST) {
        return 0.5;
    }

    else
        return 0.0;
}


void fuzzy::get_fuzzy_far(float xPosition) {
    if (xPosition <= -0.2) {
        fuzzy_value_left_far = 1;
    }
    
    if (xPosition >= 0) {
        fuzzy_value_left_far = 0;
    }
    
    if (xPosition > -0.2 && xPosition < 0) {
        fuzzy_value_left_far = -(5 * xPosition);
    }
    
    
    if (xPosition >= -0.2 && xPosition <= 0) {
        fuzzy_value_med_far = (5 * xPosition) + 1;
    }
    
    if (xPosition >= 0 && xPosition <= 0.2) {
        fuzzy_value_med_far = -(5 * xPosition) + 1;
    }
    
    if (xPosition < -0.2 || xPosition > 0.2) {
        fuzzy_value_med_far = 0;
    }
    
    if (xPosition >= 0.2) {
        fuzzy_value_right_far = 1;
    }
    
    if (xPosition <= 0) {
        fuzzy_value_right_far = 0;
    }
    
    if (xPosition > 0 && xPosition < 0.2) {
        fuzzy_value_right_far = (5 * xPosition);
    }
    
}

void fuzzy::get_fuzzy_speed(float Yvelocity) {
    if (Yvelocity < 2) {
        fuzzy_value_low_speed = 1;
    }
    
    if (Yvelocity > 4) {
        fuzzy_value_low_speed = 0;
    }
    
    if (Yvelocity >=2 && Yvelocity <=4) {
        fuzzy_value_low_speed = -(Yvelocity/2) + 2;
    }
    
    
    
    if (Yvelocity >= 3 && Yvelocity <=5) {
        fuzzy_value_med_speed = (Yvelocity / 2) - 1.5;
    }
    
    if (Yvelocity > 5 && Yvelocity <= 7) {
        fuzzy_value_med_speed = -(Yvelocity / 2) + 3.5;
    }
    
    if (Yvelocity < 3 && Yvelocity > 7) {
        fuzzy_value_med_speed = 0;
    }


    if (Yvelocity <= 6) {
        fuzzy_value_high_speed = 0;
    }
    
    if (Yvelocity >= 8) {
        fuzzy_value_high_speed = 1;
    }
    
    if (Yvelocity < 8 && Yvelocity > 6) {
        fuzzy_value_high_speed = (Yvelocity / 2) - 3;
    }
    
    
    
}

void fuzzy::get_fuzzy_height(float height) {
    if (height >= 0 && height <= 20) {
        fuzzy_value_low_height = 1;
    }
    
    if (height > 20 && height <= 40) {
        fuzzy_value_low_height = -(height / 20) + 2;
    }
    
    if (height > 40) {
        fuzzy_value_low_height = 0;
    }
    
    
    
    if (height >= 30 && height <= 50) {
        fuzzy_value_med_height = (height / 20) - 1.5;
    }
    
    if (height > 50 && height <= 70) {
        fuzzy_value_med_height = -(height / 20) + 3.5;
    }
    
    if (height > 70 || height < 30) {
        fuzzy_value_med_height = 0;
    }
    
    
    
    
    if (height >= 60 && height <= 80) {
        fuzzy_value_high_height = (height / 20) - 3;
    }
    
    if (height > 80 && height <= 100) {
        fuzzy_value_high_height = 1;
    }
    
    if (height < 60) {
        fuzzy_value_high_height = 0;
    }

}

void fuzzy::fuzzy_set_Y() {
    MAX_BURN = min(fuzzy_value_low_height, fuzzy_value_high_speed);
    MED_BURN = min(fuzzy_value_low_height, fuzzy_value_med_speed);
    MED_BURN = min(fuzzy_value_low_height, fuzzy_value_low_speed);
    
    MED_BURN = min(fuzzy_value_med_height, fuzzy_value_high_speed);
    MED_BURN = min(fuzzy_value_med_height, fuzzy_value_med_speed);
    MED_BURN = min(fuzzy_value_med_height, fuzzy_value_low_speed);
    
    MED_BURN = min(fuzzy_value_high_height, fuzzy_value_high_speed);
    MED_BURN = min(fuzzy_value_high_height, fuzzy_value_med_speed);
    NO_BURN = min(fuzzy_value_high_height, fuzzy_value_low_speed);
}

float fuzzy::defuzzy_Y() {
    if (NO_BURN > MED_BURN && NO_BURN > MAX_BURN) {
        return 0.0;
    }
    
    else if ( MED_BURN > NO_BURN && MED_BURN > MAX_BURN) {
        return 1.5;
    }
    
    else if (MAX_BURN > NO_BURN && MAX_BURN > MED_BURN) {
        return 3.0;
    }
    
    else
        return 1;

}