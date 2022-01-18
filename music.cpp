#include "music.h"

Music::Music()
{
    // Adding music files
    effect.setSource(QUrl::fromLocalFile("TomAndJerryMain quiet.wav"));
    effect.setLoopCount(QSoundEffect::Infinite); // Mode of playing
    effect.setVolume(15); // Setting Volume
    effect.play(); // Play
}

void Music::Music_Game(){
    effect.setSource(QUrl::fromLocalFile("TomAndJerryMain quiet.wav")); // Choosing a specific music
    effect.setLoopCount(QSoundEffect::Infinite); // Mode of playing
    effect.setVolume(15); // Setting Volume
    effect.play(); // Play
}
void Music::Music_Win(){
    effect.setSource(QUrl::fromLocalFile("TomAndJerryWin.wav")); // Choosing a specific music
    effect.setLoopCount(1); // Mode of playing
    effect.setVolume(15); // Setting Volume
    effect.play(); // Play
}
void Music::Music_Lose(){
    effect.setSource(QUrl::fromLocalFile("TomAndJerryLose.wav")); // Choosing a specific music
    effect.setLoopCount(1); // Mode of playing
    effect.setVolume(15); // Setting Volume
    effect.play(); // Play
}

//Toggling the Music on and off
void Music::Toggle_Music(){

    effect.setMuted(!effect.isMuted());

    // More detailed code of the previous functionality

//    if (effect.isMuted())
//        effect.setMuted(false);
//    else
//        effect.setMuted(true);

}
