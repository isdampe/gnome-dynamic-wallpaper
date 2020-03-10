#pragma once
#include <string>
#include <vector>

static const char *supported_extensions[] = {
	"jpg", "tiff", "png", "gif", "jpeg"
};

#define array_size(a) (sizeof(a) / sizeof(*a))

struct dw_session {
	std::string input_dir;
	std::vector<std::string> images;
	unsigned int current_idx;
};

enum dw_error {
	ERR_NONE,
	ERR_CANT_READ_DIR
};

enum dw_error find_images(struct dw_session &session);
void shuffle_images(struct dw_session &session);
void autoset_images(struct dw_session &session);
void set_background(std::string &image_fp);
