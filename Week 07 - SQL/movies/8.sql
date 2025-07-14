SELECT name FROM movies, people, stars ON movies.id = movie_id AND people.id = person_id WHERE title = 'Toy Story';
