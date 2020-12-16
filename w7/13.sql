-- Select people.name
SELECT people.name FROM people
WHERE people.id IN (
SELECT stars.person_id FROM stars
WHERE stars.movie_id IN (
-- From selection of movies.id
SELECT movies.id FROM movies
WHERE movies.id IN (
SELECT stars.movie_id FROM stars
WHERE person_id IN (
-- From selection where people.id is Kevin Bacon born in 1958
SELECT people.id FROM people
WHERE people.name = "Kevin Bacon"
AND people.birth = 1958))));