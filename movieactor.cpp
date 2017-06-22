#include "movieactor.hpp"
#include "messages.hpp"
#include "movie.hpp"

#include <algorithm>

void MovieActor::addMovie(Movie * _Actor)
{
	if (movies.find(_Actor->getMovieName()) != movies.end())
		throw std::logic_error(Messages::MovieActorAlreadyAdded);

	movies[_Actor->getMovieName()] = _Actor;
}

std::vector<std::string> MovieActor::getActorMovies() const
{
	std::vector<std::string> buf;

	auto it = movies.begin();
	while (it != movies.end())
	{
		buf.push_back(it->first);
		it++;
	}
	std::sort(buf.begin(), buf.end());
	return buf;
}

double MovieActor::getAverageRating() const
{
	if (movies.empty())
		return 0.0;

	double x = 0;

	auto it = movies.begin();
	while (it!= movies.end())
	{
		x += it->second->getRating();
		it++;
	}

	return x / movies.size();
}