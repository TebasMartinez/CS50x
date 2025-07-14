SELECT DISTINCT title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON people.id = stars.person_id WHERE movies.id IN
    (SELECT movie_id FROM stars WHERE person_id IN
        (SELECT id from people WHERE name = 'Bradley Cooper')
    INTERSECT
    SELECT movie_id FROM stars WHERE person_id IN
        (SELECT id from people WHERE name = 'Jennifer Lawrence'));
