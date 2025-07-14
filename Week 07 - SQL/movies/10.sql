SELECT DISTINCT name FROM directors, ratings, people ON directors.movie_id = ratings.movie_id AND person_id = id
WHERE rating >= 9.0;
