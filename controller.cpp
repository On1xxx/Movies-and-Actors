#include "controller.hpp"

#include "messages.hpp"
#include "movie.hpp"
#include "movieactor.hpp"
#include "datetime.hpp"

#include <algorithm>

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::createActor(std::string const & _actorName, int _birthYear)
{
	if (_actorName.empty())
		throw std::logic_error(Messages::ActorNameEmpty);

	if (_birthYear > DateTime().getYear())
		throw std::logic_error(Messages::ActorBornInFuture);

	auto found = movie_actors.find(_actorName);
	if (found != movie_actors.end())
		throw std::logic_error(Messages::ActorAlreadyRegistered);


	movie_actors[_actorName] = std::unique_ptr<MovieActor>( new MovieActor(_actorName, _birthYear) );
}

int Controller::getActorBirthYear(std::string const & _actorName) const
{
	if (_actorName.empty())
		throw std::logic_error(Messages::ActorNameEmpty);
	
	auto found = movie_actors.find(_actorName);
	if (found == movie_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	return found->second->getBirthDate();
}

void Controller::createMovie(std::string const & _movieTitle, int _productionYear, int _rating)
{
	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	if (_productionYear > DateTime().getYear())
		throw std::logic_error(Messages::MovieProducedInFuture);

	if (_rating < 1 || _rating > 10)
		throw std::logic_error(Messages::RatingOutOfRange);

	auto found = movies.find(_movieTitle);
	if (found != movies.end())
		throw std::logic_error(Messages::MovieAlreadyRegistered);

	movies[_movieTitle] = std::unique_ptr<Movie>( new Movie(_movieTitle, _productionYear, _rating) );
}

int Controller::getMovieProductionYear(std::string const & _movieTitle) const
{
	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	auto found = movies.find(_movieTitle);
	if (found == movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	return found->second->getFoundDate();
}

int Controller::getMovieRating(std::string const & _movieTitle) const
{
	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	auto found = movies.find(_movieTitle);
	if (found == movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	return found->second->getRating();
}

void Controller::addMovieGenre(std::string const & _movieTitle, std::string const & _genre)
{
	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	if (_genre.empty())
		throw std::logic_error(Messages::GenreNameEmpty);

	auto & found = movies.find(_movieTitle);
	if (found == movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	found->second->addGenre(_genre);
}

std::vector<std::string> Controller::getMovieGenres(std::string const & _movieTitle) const
{
	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	auto found = movies.find(_movieTitle);
	if (found == movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	return found->second->getMovieGenres();
}

std::vector<std::string> Controller::getGenreMovies(std::string const & _genre) const
{
	if (_genre.empty())
		throw std::logic_error(Messages::GenreNameEmpty);

	std::vector<std::string> res;

	auto found = movies.begin();
	while (found != movies.end())
	{
		if (found->second->isGotGenre(_genre))
			res.push_back(found->second->getMovieName());
		found++;
	}

	return res;
}

void Controller::addMovieActor(std::string const & _movieTitle, std::string const & _actorName)
{
	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	if (_actorName.empty())
		throw std::logic_error(Messages::ActorNameEmpty);

	auto & found = movies.find(_movieTitle);
	if (found == movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	auto foundA = movie_actors.find(_actorName);
	if (foundA == movie_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	found->second->addActor
	(
		new MovieActor(_actorName, found->second->getFoundDate() - foundA->second->getBirthDate()) 
	);
	foundA->second->addMovie(found->second.get());	
}

std::vector<std::string> Controller::getMovieActors(std::string const & _movieTitle) const
{
	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	auto found = movies.find(_movieTitle);
	if (found == movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	return found->second->getMovieActors();
}

std::vector<std::string> Controller::getActorMovies(std::string const & _actorName) const
{
	if (_actorName.empty())
		throw std::logic_error(Messages::ActorNameEmpty);

	auto found = movie_actors.find(_actorName);
	if (found == movie_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	return found->second->getActorMovies();
}

std::string Controller::getOldestMovieOfGenre(std::string const & _genre) const
{
	if(_genre.empty())
		throw std::logic_error(Messages::GenreNameEmpty);

	if (movies.empty())
		return "";

	std::string oldest;
	int old = DateTime().getYear();

	auto it = movies.begin();
	while (it != movies.end())
	{
		if (it->second->isGotGenre(_genre))
			if (it->second->getFoundDate() < old)
			{
				old = it->second->getFoundDate();
				oldest = it->second->getMovieName();
			}

		it++;
	}


	return oldest;
}

double Controller::getActorAverageRating(std::string const & _actorName) const
{
	auto found = movie_actors.find(_actorName);
	if (found == movie_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	return found->second->getAverageRating();
}

std::vector<std::string> Controller::getActorsThatNeverPlayedInGenre(std::string const & _genre) const
{
	std::vector<std::string> res = getGenreMovies(_genre);

	std::vector<std::string> act;
	for (int i = 0; i < res.size(); i++)
	{
		std::vector<std::string> buf = getMovieActors(res[i]);
		for (int j = 0; j < buf.size(); j++)
			act.push_back(buf[j]);
	}

	res.clear();

	auto it = movie_actors.begin();
	while (it != movie_actors.end())
	{
		if (std::find(act.begin(), act.end(), it->first) == act.end())
			res.push_back(it->first);

		it++;
	}
	

	return res;
}

std::vector<std::string> Controller::getMoviesWhenActorWasYoungerThan(std::string const & _actorName, int _age) const
{
	if (_age <= 0)
		throw std::logic_error(Messages::NegativeAge);

	std::vector<std::string> res;

	std::vector<std::string> films = getActorMovies(_actorName);

	for (int i = 0; i < films.size(); i++)
	{
		auto it = movies.find(films[i]);
		if (it != movies.end())
		{
			if (it->second->getActorByName(_actorName)->getBirthDate() < _age)
				res.push_back(it->first);
		}
	}

	std::sort(res.begin(), res.end());
	return res;
}
