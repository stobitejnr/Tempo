#include "Timer.h"

class Timer{

    private:
    int id;
    bool running;

    public:
    Timer::Timer(int t_hours, int t_minutes, int t_seconds, int t_id, bool t_run){
        id = t_id;
        running = t_run;
    }
};
