SELECT DISTINCT name FROM movies, people, stars ON movies.id = movie_id AND people.id = person_id
WHERE year = '2004'
ORDER BY birth;
