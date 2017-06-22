#include "movie.hpp"
#include "movieactor.hpp"
#include "messages.hpp"

#include <algorithm>

void Movie::addGenre(std::string const & _Genre)
{
	if (genres.find(_Genre) != genres.end())
		throw std::logic_error(Messages::MovieGenreAlreadyAdded);

	genres.insert(_Genre);
}

std::vector<std::string> Movie::getMovieGenres() const
{
	std::vector<std::string> result;

	auto it = genres.begin();
	while (it != genres.end())
	{
		result.push_back(*it);
		it++;
	}

	return result;
}

void Movie::addActor(MovieActor * _Actor)
{
	if (genres.find(_Actor->getFullName()) != genres.end())
		throw std::logic_error(Messages::ActorAlreadyRegistered);

	actors[_Actor->getFullName()] = _Actor;
}

std::vector<std::string> Movie::getMovieActors() const
{
	std::vector<std::string> result;

	auto it = actors.begin();
	while (it != actors.end())
	{
		result.push_back(it->first);
		it++;
	}

	std::sort(result.begin(), result.end());
	return result;
}

bool Movie::isGotGenre(std::string const & _Genre) const
{
	return genres.find(_Genre) != genres.end();
}

MovieActor * Movie::getActorByName(std::string const & _Name)
{
	return actors[_Name];
}