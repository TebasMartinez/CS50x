SELECT title FROM movies, people, ratings, stars ON movies.id = ratings.movie_id AND people.id = person_id AND movies.id = stars.movie_id
WHERE name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;
