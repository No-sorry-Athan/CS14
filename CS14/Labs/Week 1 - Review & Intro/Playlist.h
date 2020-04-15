#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>
using namespace std;
#include <iostream>

struct PlaylistNode {
private:
	string uniqueID;
	string songName;
	string artistName;
	int songLength;
	PlaylistNode* nextNodePtr;
public:
	//Constructors
	PlaylistNode();
	PlaylistNode(string, string, string, int);

	//Mutators
	void InsertAfter(PlaylistNode*);
	void SetNext(PlaylistNode*);

	//Accessors
	const string GetID() const;
	const string GetSongName() const;
	const string GetArtistName() const;
	const int GetSongLength() const;
	PlaylistNode* GetNext() const;

	//Display
	void PrintPlaylistNode();
};


class Playlist {
private:
	string name;
	PlaylistNode* head;
	PlaylistNode* tail;
public:
	Playlist(string);
	const string getPlayListName() const;
	const bool isEmpty() const;
	void outputFullPlaylist() const;
	void outputFullTime() const;
	void outputByArtist(string) const;

	void addSong(PlaylistNode*);
	void removeSong(string);
	void moveSong(int, int);
	int numNodes() const;
};
#endif // !PLAYLIST_H
