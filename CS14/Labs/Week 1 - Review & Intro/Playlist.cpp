#include "Playlist.h"


PlaylistNode::PlaylistNode() {
	uniqueID = "none";
	songName = "none";
	artistName = "none";
	songLength = 0;
	nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string id, string sName, string aName, int songDur) {
	uniqueID = id;
	songName = sName;
	artistName = aName;
	songLength = songDur;
	nextNodePtr = 0;
}

void PlaylistNode::InsertAfter(PlaylistNode* node) {
	if (node) {
		node->nextNodePtr = this->nextNodePtr;
		nextNodePtr = node;
	}
}

void PlaylistNode::SetNext(PlaylistNode* node) {
	nextNodePtr = node;
}

const string PlaylistNode::GetID() const {
	return uniqueID;
}

const string PlaylistNode::GetSongName() const {
	return songName;
}

const string PlaylistNode::GetArtistName() const {
	return artistName;
}

const int PlaylistNode::GetSongLength() const {
	return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
	return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() {
	cout << "Unique ID: " << uniqueID << endl;
	cout << "Song Name: " << songName << endl;
	cout << "Artist Name: " << artistName << endl;
	cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::Playlist(string name) : name(name), head(0), tail(0){}

const string Playlist::getPlayListName() const{
	return name;
}

const bool Playlist::isEmpty() const {
	return (head == nullptr && tail == nullptr);
}

void Playlist::outputFullPlaylist()	const {
	if (isEmpty()) {
		cout << "Playlist is empty" << endl;
		cout << endl;
		return;
	}
	PlaylistNode* node = head;
	int index = 1;
	while (node) {
		cout << index << "." << endl;
		node->PrintPlaylistNode();
		cout << endl;
		node = node->GetNext();
		index++;
	}
}

void Playlist::outputFullTime() const {
	int totalTime = 0;
	PlaylistNode* node = head;
	while (node) {
		totalTime += node->GetSongLength();
		node = node->GetNext();
	}
	cout << "Total time: " << totalTime << " seconds" << endl;
}

void Playlist::outputByArtist(string artN) const {
	PlaylistNode* node = head;
	int index = 1;
	while (node) {
		if (node->GetArtistName() == artN) {
			cout << index << "." << endl;
			node->PrintPlaylistNode();
			cout << endl;
		}
		node = node->GetNext();
		index++;
	}
}

void Playlist::addSong(PlaylistNode* node) {
	if (isEmpty()) {
		head = node;
		tail = node;
	}
	else {
		tail->SetNext(node);
		tail = node;
	}
}

void Playlist::removeSong(string uID) {
	if (isEmpty())
		return;

	PlaylistNode* node = head;
	if (head == tail) {
		if (node->GetID() == uID) {
			cout << "\"" << node->GetSongName() << "\" removed." << endl;
			delete node;
			head = nullptr;
			tail = nullptr;
			return;
		}
	}

	PlaylistNode* next = node->GetNext();
	while (node) {
		if (next->GetID() == uID) {
			node->SetNext(next->GetNext());
			cout << "\"" << next->GetSongName() << "\" removed." << endl;
			if (next == tail)
				tail = node;
			delete next;
			return;
		}
		node = node->GetNext();
		next = next->GetNext();
	}
}

void Playlist::moveSong(int des, int curr) {
	if (isEmpty())
		return;
	int numNode = numNodes();

	PlaylistNode* desPointer = head;
	PlaylistNode* curPointer = head;
	PlaylistNode* beforeDes = head;
	PlaylistNode* beforeCur = head;

	int index = 1;
	while (desPointer) {
		if (index + 1 == des)
			beforeDes = desPointer;
		if (index == des) 
			break;
		index++;
		desPointer = desPointer->GetNext();
	}

	index = 1;
	while (curPointer) {
		if (index + 1 == curr)
			beforeCur = curPointer;
		if (index == curr)
			break;
		index++;
		curPointer = curPointer->GetNext();
	}

	if (curr == 1) { // moving head
		PlaylistNode* node = head->GetNext();
		
		//curPointer->InsertAfter(beforeDes);
		curPointer->SetNext(desPointer->GetNext());
		desPointer->SetNext(curPointer);
		head = node;
		if (des == numNode) {
			tail = curPointer;
		}
	}
	else if (curr == numNode) { // moving tail
		PlaylistNode* beforeTail = head;

		while (beforeTail) {
			if (beforeTail->GetNext() == tail)
				break;
			beforeTail = beforeTail->GetNext();
		}
		beforeTail->SetNext(nullptr);
		tail->SetNext(desPointer);
		//beforeDes->SetNext(tail->GetNext());
		if (des == 1) {
			head = curPointer;
		}
		tail = beforeTail;
	}
	else if (des == 1) { // moving to head
		beforeCur->SetNext(curPointer->GetNext());
		curPointer->SetNext(head);
		head = curPointer;
	}
	else if (des == numNode) {// moving node up to tail
		beforeCur->SetNext(curPointer->GetNext());
		curPointer->SetNext(0);
		tail->SetNext(curPointer);
		tail = curPointer;
	}
	else if (des > curr) { //moving node up list
		beforeCur->SetNext(curPointer->GetNext());

		curPointer->SetNext(desPointer->GetNext());
		desPointer->SetNext(curPointer);
		//curPointer->InsertAfter(desPointer);

	}
	else if (des < curr) { //moving node down list
		beforeCur->SetNext(curPointer->GetNext());

		//curPointer->InsertAfter(desPointer);

		curPointer->SetNext(desPointer);
		beforeDes->SetNext(curPointer);

	}
	cout << "\"" << curPointer->GetSongName() << "\" moved to position " << des << endl;

}

int Playlist::numNodes() const{
	PlaylistNode* node = head;
	int index = 0;
	while (node) {
		index++;
		node = node->GetNext();
	}

	return index;
}

