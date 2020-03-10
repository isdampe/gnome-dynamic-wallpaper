#include <algorithm>
#include <string>
#include <iostream>
#include <filesystem>
#include <random>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>
#include "dynamic-wallpaper.h"

enum dw_error find_images(struct dw_session &session)
{
	for (const auto &entry : std::filesystem::directory_iterator(session.input_dir)) {
		std::string file = std::string(entry.path());
		std::string ext = file.substr(file.find_last_of(".") + 1);

		for (auto i=0; i<array_size(supported_extensions); ++i) {
			if (ext == supported_extensions[i]) {
				session.images.push_back(std::string(entry.path()));
			}
		}
	}

	return dw_error::ERR_NONE;
}

void shuffle_images(struct dw_session &session)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(std::begin(session.images), std::end(session.images), e);
}

void autoset_images(struct dw_session &session)
{
	while (1) {
		set_background(session.images[session.current_idx]);
		session.current_idx = (session.current_idx + 1) % session.images.size();

		sleep(3600);
	}
}

void set_background(std::string &image_fp)
{
	std::string cmd = "gsettings set org.gnome.desktop.background picture-uri file:///" + image_fp;
	system(cmd.c_str());
}

int main(const int argc, const char **argv)
{
	if (argc < 2) {
		std::cerr << "Usage: dynamic-wallpaper [input_directory]" << std::endl;
		return 1;
	}

	struct dw_session session;
	session.input_dir = std::string(argv[argc -1]);	
	session.current_idx = 0;

	if (find_images(session) != dw_error::ERR_NONE) {
		std::cerr << "Error reading input images." << std::endl;
		return 1;
	}

	std::cout << "Found " << session.images.size() << 
		" images to cycle through" << std::endl;

	shuffle_images(session);
	autoset_images(session);

	return 0;
}
