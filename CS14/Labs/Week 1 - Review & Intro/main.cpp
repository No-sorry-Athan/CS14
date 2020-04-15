#include "Playlist.h"
using namespace std;

void PrintMenu(Playlist&);

int main() {
	string plTitle;
	cout << "Enter playlist's title:" << endl;
	getline(cin, plTitle);
	cout << endl;
	Playlist pl(plTitle);
	PrintMenu(pl);
	return 0;
}

void PrintMenu(Playlist& pl) {
	cout << pl.getPlayListName() << " PLAYLIST MENU" << endl;
	cout << "a - Add song" << endl;
	cout << "d - Remove song" << endl;
	cout << "c - Change position of song" << endl;
	cout << "s - Output songs by specific artist" << endl;
	cout << "t - Output total time of playlist (in seconds)" << endl;
	cout << "o - Output full playlist" << endl;
	cout << "q - Quit" << endl;
	cout << endl;
	cout << "Choose an option:" << endl;
	string choice;
	cin >> choice;
	while (choice != "q") {
		if (choice == "a") {
			string uID;
			string sName;
			string aName;
			int songDur;

			cout << "ADD SONG" << endl;
			cout << "Enter song's unique ID:" << endl;
			cin >> uID;
			cin.ignore();
			cout << "Enter song's name:" << endl;
			getline(cin, sName);
			//cin.ignore();
			cout << "Enter artist's name:" << endl;
			getline(cin, aName);
			//cin.ignore();
			cout << "Enter song's length (in seconds):" << endl;
			cin >> songDur;

			PlaylistNode* newSong = new PlaylistNode(uID, sName, aName, songDur);
			pl.addSong(newSong);
			cout << endl;
		}
		else if (choice == "d") {
			string uID;
			cout << "REMOVE SONG" << endl;
			cout << "Enter song's unique ID:" << endl;
			cin >> uID;
			pl.removeSong(uID);
			cout << endl;
		}
		else if (choice == "c") {
			int currInd;
			int desInd;
			cout << "CHANGE POSITION OF SONG" << endl;
			cout << "Enter song's current position:" << endl;
			cin >> currInd;
			cout << "Enter new position for song:" << endl;
			cin >> desInd;
			pl.moveSong(desInd, currInd);
			cout << endl;
		}
		else if (choice == "s") {
			cin.ignore();
			string artName;
			cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
			cout << "Enter artist's name:" << endl;
			getline(cin, artName);
			cout << endl;
			pl.outputByArtist(artName);
		}
		else if (choice == "t") {
			cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
			pl.outputFullTime();
			cout << endl;
		}
		else if (choice == "o") {
			cout << pl.getPlayListName() << " - OUTPUT FULL PLAYLIST" << endl;
			pl.outputFullPlaylist();
		}
		else if (choice == "q") {
			break;
		}

		cout << pl.getPlayListName() << " PLAYLIST MENU" << endl;
		cout << "a - Add song" << endl;
		cout << "d - Remove song" << endl;
		cout << "c - Change position of song" << endl;
		cout << "s - Output songs by specific artist" << endl;
		cout << "t - Output total time of playlist (in seconds)" << endl;
		cout << "o - Output full playlist" << endl;
		cout << "q - Quit" << endl;
		cout << endl;
		cout << "Choose an option:" << endl;
		cin >> choice;
	}
}
