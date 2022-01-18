#ifndef MUSIC_H
#define MUSIC_H
#include <QtMultimedia>
#include <QSoundEffect>

class Music
{
    private:
        QSoundEffect effect;

    public:
        Music();

        void Music_Game();
        void Music_Win();
        void Music_Lose();
        void Toggle_Music();
    };

#endif // MUSIC_H
