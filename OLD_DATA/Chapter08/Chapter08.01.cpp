// 04/02/2026
// Chapter08.01.cpp
// Exercises

//
// [1] List plausible operations for the examples of real-world objects in §8.1 (e.g., a toaster).
//

#include "PPPheaders.h"

class Toaster {
public:
	Toaster() :heat_setting{ 1.0 } {}
	Toaster(double d) :heat_setting{ d } {}
 
	double getHeatSetting();
	void startToasting();		// uses heat_setting
	void stopToasting();
	void ejectToast();
 
private:
	double heat_setting;
};

class Music_player {
public:
	Music_player() :current{getCurrentSong()} {}
	
	struct Song {
		string name;
		double length;
	};

	Song getCurrentSong();
	void playSong();			// uses current
	void toggleShuffle();		// modifies shuffle_enabled
	void toggleRepitition();	// modifies repitition_enabled

private:
	Song current;
	bool shuffle_enabled = false;
	bool repitition_enabled = false;
	vector<Song> playlist;
};

