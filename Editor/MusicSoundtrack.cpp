#include "MusicSoundtrack.h"
#include <iostream>
#include <unistd.h>

EditorSoundtrack::EditorSoundtrack():suspense("../Music/06-Suspense E1M4.mp3"),\
    pow("../Music/05-P.O.W. E1M3.mp3"),EnemyAround("..Music/08-Enemy Around the Corner E1M10.mp3"){
    
}

void EditorSoundtrack::load_editor_soundtrack(){
    
   // SdlMusic music("../Music/06-Suspense E1M4.mp3");
    //music3("../Music/06-Suspense E1M4.mp3");
    //music3("../Music/06-Suspense E1M4.mp3");
    //songs.push_back(music3);
}

void EditorSoundtrack::play_editor(){
    suspense.play();
   // pow.play();
    //EnemyAround.play();
    
    //songs.at(0).play();
}

EditorSoundtrack::~EditorSoundtrack(){

}