#include "SdlClasses/SdlMusic.h"
#include <vector>
#include <map>

class EditorSoundtrack{
private:
    //std::vector<SdlMusic> songs;
    SdlMusic suspense;
    SdlMusic pow;
    SdlMusic EnemyAround;

public:
    EditorSoundtrack();

    void load_editor_soundtrack();

    void play_editor();

	~EditorSoundtrack();
};

