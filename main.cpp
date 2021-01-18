//Using STL to
//make a Playlist

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

class Song {
	friend std::ostream& operator<<(std::ostream& os, const Song& s);
	std::string name;
	std::string artist;
	int rating;
public:
	Song() = default;
	Song(std::string name, std::string artist, int rating)
		: name{ name }, artist{ artist }, rating{ rating } {}
	std::string get_name() const {
		return name;
	}
	std::string get_artist() const {
		return artist;
	}
	int get_rating() const {
		return rating;
	}

	bool operator<(const Song& rhs) const {
		return this->name < rhs.name;
	}
	
	bool operator==(const Song& rhs) const {
		return this->name == rhs.name;
	}
};

std::ostream& operator<<(std::ostream& os, const Song& s) {
	os << std::setw(20) << std::left << s.name
		<< std::setw(30) << std::left << s.artist
		<< std::setw(2) << std::left << s.rating;
	return os;
}

void display_menu() {
	std::cout << "\nF - Play First Song" << std::endl;
	std::cout << "N - Play Next Song" << std::endl;
	std::cout << "P - Play Previous Song" << std::endl;
	std::cout << "A - Add and a play a new Song at current location" << std::endl;
	std::cout << "L - List the current playlist" << std::endl;
	std::cout << "====================================================" << std::endl;
	std::cout << "Enter a SELECTION (Q to Quit): ";
}

void play_current_song(const Song& song) {
	std::cout << "Now Playing:" << std::endl;
	std::cout << song << std::endl;
}

void display_playlist(const std::list<Song>& playlist, const Song& current_song) {
	for (const Song& song : playlist) {
		std::cout << song << std::endl;
	}
	std::cout << "Currently Playing:" << std::endl;
	std::cout << current_song << std::endl;
}

int main() {

	std::list<Song> playlist{
		{"Alfred's Theme",					"Eminem",					5},
		{"Blonde",							"Ivy Lab",					4},
		{"DR BIRDS",						"Griselda",					5},
		{"Young",							"Lord and the Woolf",		4},
		{"Veryovkina",						"SZRCA",					5},
		{"Daytona",							"Commodo",					5}
	};

	std::list<Song>::iterator current_song = playlist.begin();
	display_playlist(playlist, *current_song);

	char input;
	do {
		display_menu();
		std::cin >> input;
		input = std::toupper(input);
		if (input == 'F') {
			std::cout << "\n";
			current_song = playlist.begin();
			play_current_song(*current_song);
			std::cout << "\n";
		}
		else if (input == 'N') {
			std::cout << "\n";
			if (current_song == playlist.end()) {
				current_song == playlist.begin();
			}
			current_song++;
			play_current_song(*current_song);
			std::cout << "\n";
		}
		else if (input == 'P') {
			std::cout << "\n";
			if (current_song == playlist.begin()) {
				current_song == playlist.end();
			}
			current_song--;
			play_current_song(*current_song);
			std::cout << "\n";
		}
		else if (input == 'A') {
			std::string new_name;
			std::string new_artist;
			int new_rating;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "\n";
			std::cout << "Enter Song name: ";
			getline(std::cin, new_name);
			std::cout << "Enter Artist name: ";
			getline(std::cin, new_artist);
			std::cout << "Enter Rating: ";
			std::cin >> new_rating;
			Song new_song{ new_name, new_artist, new_rating };
			playlist.insert(current_song, new_song);
			current_song--;
			std::cout << "\n";
			play_current_song(*current_song);
			std::cout << "\n";
		}
		else if (input == 'L') {
			std::cout << "\n";
			display_playlist(playlist, *current_song);
			std::cout << "\n";
		}
		else if (input == 'Q') {
			std::cout << "Quitting" << std::endl;
		}
		else {
			std::cout << "Invalid input - please try again..";
		}
	} while (std::toupper(input) != 'Q');

	return 0;
}
