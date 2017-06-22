#ifndef _MOVIEACTOR_HPP_
#define _MOVIEACTOR_HPP_

/*****************************************************************************/

#include <string>

/*****************************************************************************/

class Movie;

/*****************************************************************************/

#include <map>
#include <vector>

class MovieActor
{

	std::string FullName;
	int BirthDate;
	std::map<std::string, Movie*> movies;

public:
	
	MovieActor(std::string const & _Name, int _Birth = -1);

	const std::string getFullName() const;
	const int getBirthDate() const;

	void addMovie(Movie * _Actor);

	std::vector<std::string> getActorMovies() const;
	double getAverageRating() const;
};


inline
MovieActor::MovieActor(std::string const & _Name, int _Birth)
	:FullName(_Name), BirthDate(_Birth)
{
}

inline
const std::string MovieActor::getFullName() const
{
	return FullName;
}

inline
const int MovieActor::getBirthDate() const
{
	return BirthDate;
}


/*****************************************************************************/

#endif //  _MOVIEACTOR_HPP_