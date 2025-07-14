SELECT title, rating FROM movies, ratings ON movies.id = movie_id WHERE year = '2010' ORDER BY rating DESC, title;
