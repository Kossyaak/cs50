Select title from movies
    where id IN (
        select movie_id
        from stars
        where person_id IN (
                select id
                from people
                where name = "Helena Bonham Carter"
            )
        INTERSECT
        select movie_id
        from stars
        where person_id IN (
                select id
                from people
                where name = "Johnny Depp"
            )
    );