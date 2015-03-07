#ifndef FUZZY_H
#define FUZZY_H
#include <iostream>

using namespace std;

class fuzzy {

    public:
    
        // For Y-Position
        void get_fuzzy_height(float height);
        void get_fuzzy_speed(float Yvelocity);
        void fuzzy_set_Y();
        float defuzzy_Y();
    
        void get_fuzzy_far(float xPosition);
        void fuzzy_set_X();
        float defuzzy_X();
    
    
    private:
        float height;
        float Yvelocity;
        
        double fuzzy_value_low_height;
        double fuzzy_value_med_height;
        double fuzzy_value_high_height;
        double fuzzy_value_low_speed;
        double fuzzy_value_med_speed;
        double fuzzy_value_high_speed;

        double fuzzy_value_left_far;
        double fuzzy_value_med_far;
        double fuzzy_value_right_far;

    
    
        double NO_BURN;
        double MED_BURN;
        double MAX_BURN;
        double RIGHT_THURST;
        double NO_THURST;
        double LEFT_THURST;
    
    
    
};



#endif
