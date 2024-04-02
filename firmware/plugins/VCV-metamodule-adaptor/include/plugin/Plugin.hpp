#pragma once
#include <string>
#include <vector>

namespace rack::plugin
{

struct Model;
struct json_t;

// Subclass this and return a pointer to a new one when init() is called
struct Plugin {
	Plugin()
		: slug{""} {
	}

	Plugin(std::string slug)
		: slug{slug} {
	}

	// Owning pointers: TODO unique_ptr (or will that break the VCV API?)
	std::vector<Model *> models;

	std::string slug; //brand slug

	//TODO: do we need all the string fields:
	// version, license, name, brand, ...
	void addModel(Model *model);
	~Plugin();

	Model *getModel(const std::string &slug);
	std::string getBrand();

	void fromJson(json_t *rootJ) {
	}
	void modulesFromJson(json_t *rootJ) {
	}

	//TODO do we need these?
	// std::string path;
	// void *handle = nullptr;
	// std::string version;
	// std::string license;
	// std::string name;
	// std::string brand;
	// std::string description;
	// std::string author;
	// std::string authorEmail;
	// std::string authorUrl;
	// std::string pluginUrl;
	// std::string manualUrl;
	// std::string sourceUrl;
	// std::string donateUrl;
	// std::string changelogUrl;
	// double modifiedTimestamp{};
};

} // namespace rack::plugin
