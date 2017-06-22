#ifndef _MOVIE_HPP_
#define _MOVIE_HPP_

/*****************************************************************************/

#include <string>
#include <set>
#include <map>
#include <vector>

/*****************************************************************************/

class MovieActor;

/*****************************************************************************/


class Movie
{

	std::string MovieName;
	int FoundDate;
	int Rating;
	std::set<std::string> genres;
	std::map<std::string, MovieActor*> actors;

public:

	Movie(std::string const & _Name, int _Date, int _Rating);

	const std::string & getMovieName() const;
	const int getFoundDate() const;
	const int getRating() const;

	void addGenre(std::string const & _Genre);
	void addActor(MovieActor * _Actor);

	bool isGotGenre(std::string const & _Genre) const;
	std::vector<std::string>  getMovieGenres() const;
	std::vector<std::string> getMovieActors() const;

	MovieActor * getActorByName(std::string const & _Name);
};


inline
Movie::Movie(std::string const & _Name, int _Date, int _Rating)
	:MovieName(_Name), FoundDate(_Date), Rating(_Rating)
{
}

inline
const std::string & Movie::getMovieName() const
{
	return MovieName;
}

inline
const int Movie::getFoundDate() const
{
	return FoundDate;
}

inline
const int Movie::getRating() const
{
	return Rating;
}

/*****************************************************************************/


#endif //  _MOVIE_HPP_