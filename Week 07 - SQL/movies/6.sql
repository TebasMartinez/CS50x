SELECT AVG(rating) FROM movies, ratings ON movies.id = movie_id WHERE year = '2012';
