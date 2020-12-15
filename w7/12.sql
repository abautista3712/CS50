SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Johnny Depp"
OR people.name ="Helena Bonham Carter"
GROUP BY movies.title
HAVING COUNT(movies.title) > 1;