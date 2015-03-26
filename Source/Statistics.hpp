#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Window.hpp"
#include "ResourceHolder.hpp"

class Statistics
{
	public:
		static Statistics* instance();

		static void add(std::string const& field, std::string const& defaultValue = "");

		static void setValue(std::string const& field, std::string const& value);

		static void setFont(std::string const& filename);
		static void setCharSize(unsigned int charSize);

		static void render();

	private:
        Statistics();
        ~Statistics();

        void update();

		static Statistics gInstance;
		static bool gInitialised;

		std::shared_ptr<sf::Font> mFont;
		unsigned int mCharSize;
		std::map<std::string,sf::Text> mStats;
};


#endif // STATISTICS_HPP
