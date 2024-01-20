#include "sound.h"

void wait_ticks(int ticks)
{
    int i = ticks;
    while (i != 0) {
        --i;
    }
}

void play_sound(char* soundFile)
{
        char soundpath[256] = "./sound/";
        char command[256];
        strcat(soundpath, soundFile);
#ifdef _WIN32
        snprintf(command, sizeof(command), "start %s", soundpath);
        system(command);
#else
        snprintf(command, sizeof(command), "open %s", soundpath);
        system(command);
        system("xdotool getactivewindow windowkill");
#endif

}
