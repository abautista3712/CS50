SELECT movies.title, people.name, people.birth FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Kevin Bacon"
AND people.birth = 1958;