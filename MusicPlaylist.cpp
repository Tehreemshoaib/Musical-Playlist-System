#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Node {
    string songname; 
    Node* next;
    Node* previous;
};

class LinkedList {
public:
    Node* head;
    Node* currentsong;
    LinkedList() {
        head = nullptr;
        currentsong = nullptr;
        load_my_playlist();
    }
    void save_my_playlist() {
        ofstream file("playlist.txt");
        Node* current = head;
        while (current) {
            file << current->songname << endl;
            current = current->next;
        }
        file.close();
    }
    void load_my_playlist() {
        ifstream file("playlist.txt");
        if (!file) {
            cout << "There's no existing playlist" << endl;
            return;
        }

        string song;
        while (getline(file, song)) {
            add(song, false);
        }
        file.close();
    }
    void add(string name, bool save = true) {
        Node* temp = new Node;
        temp->songname = name;
        temp->next = nullptr;
        temp->previous = nullptr;

        if (head == nullptr) {
            head = temp;
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = temp;
            temp->previous = current;
        }
        if (save) save_my_playlist();
    }

    void remove(string songtoremove) {
        Node* current = head;
        while (current != nullptr) {
            if (current->songname == songtoremove) {
                Node* temp = current;
                if (current == head) { /*first case where the node is head*/
                    head = current->next;
                    if (head != nullptr) {
                        head->previous = nullptr;
                    }
                }
                else if (current->next == nullptr) { /*where the node is in the last*/
                    current->previous->next = nullptr;
                }
                else { /*where the node is in the middle*/
                    current->previous->next = current->next;
                    current->next->previous = current->previous;
                }
                delete temp;
                save_my_playlist();
                return;
            }
            current = current->next;
        }
        cout << "This song doesn't exist in the playlist!";
    }

    void play(string toplay) {

        if (head == nullptr) {
            cout << "\nNo songs in the playlist." << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            if (current->songname == toplay) {
                currentsong = current;
                cout << "\033[31mNow playing: " << currentsong->songname << "\033[0m" << endl;
                return;
            }
            current = current->next;
        }

    }
    void next() {
        if (currentsong == nullptr) {
            cout << "\nNo song currently playing." << endl;
            return;
        }
        if (currentsong->next == nullptr) {
            cout << "\nNo more songs to play.";
        }
        else {
            currentsong = currentsong->next;
            play(currentsong->songname);
        }
    }
    void previous() {
        if (currentsong == nullptr) {
            cout << "\nNo song playing at the moment." << endl;
            return;
        }
        if (currentsong->previous == nullptr) {
            cout << "\nFirst song in the playlist, no more previous songs.";
        }
        else {
            currentsong = currentsong->previous;
            play(currentsong->songname);
        }
    }
    void display() {
        if (head == nullptr) {
            cout << "\nThe music playlist is empty!" << endl;
        }
        Node* current = head;
        cout << "\nYour existing playlist is:\n";
        int i = 1;
        while (current != nullptr) {
            if (current == currentsong) {
                cout << i << ". \033[31m" << current->songname << "\033[0m" << "\n";
            }
            else {
                cout << i << "." << current->songname << endl;
            }
            current = current->next;
            i++;
        }
    }
    void stop() {
        if (currentsong == nullptr) {
            cout << "\nNo song is currently playing.";
        }
        else {
            cout << "\nStopped playing:" << currentsong->songname << endl;
            currentsong = nullptr;
        }
    }
    void autoplay() {
        if (head == nullptr) {
            cout << "\nThe playlist is empty! Add songs to start autoplay." << endl;
            return;
        }
        currentsong = head;
        while (currentsong != nullptr) {
            play(currentsong->songname);
            currentsong = currentsong->next;
        }
        cout << "\nReached the end of the playlist." << endl;

    }
    void menu() {
        cout << "\n***********************************";
        cout << "\nThe functions you can perform:";
        cout << "\n1.Add song";
        cout << "\n2.Delete song";
        cout << "\n3.Play song";
        cout << "\n4.Stop playing(Press S to stop)";
        cout << "\n5.Previous song(Press P for previous)";
        cout << "\n6.Next song(Press N for going to next)";
        cout << "\n7.Auto play(Press A for autoplaying)";
        cout << "\n0. Exit";

        cout << "\nEnter the action you want to be performed: ";
    }
};

int main() {
    char enter;
    string songtoremove;
    string name;
    string toplay;
    LinkedList list; // declaring an object list of the linkedlist type
    cout << "\n";
    cout << "                 ***********************************\n";
    cout << "                          MUSIC PLAYLIST          ";
    cout << "\n                 ***********************************";

    while (true) {
        list.display();
        list.menu();
        cin >> enter;
        if (enter == '1') {
            cout << "\nEnter the song to add: ";
            cin.ignore();
            getline(cin, name);
            list.add(name);
        }
        else if (enter == '2') {
            cout << "\nEnter the song to delete: ";
            cin.ignore(); // to skip extra characters like newline after reading an input.
            getline(cin, songtoremove); 
            list.remove(songtoremove);
        }
        else if (enter == '3') {
            cout << "\nEnter the song you want to play: ";
            cin.ignore();
            getline(cin, toplay);
            list.play(toplay);
        }
        else if (enter == '0') {
            cout << "\nExiting the program.";
            break;
        }
        else if (enter == 's' || enter == 'S') {
            list.stop();
        }
        else if (enter == 'p' || enter == 'P') {
            list.previous();
        }
        else if (enter == 'n' || enter == 'N') {
            list.next();
        }
        else if (enter == 'a' || enter == 'A') {
            list.autoplay();
        }
        else {
            cout << "\nInvalid option! Please try again.";
        }
    }

    return 0;
}
